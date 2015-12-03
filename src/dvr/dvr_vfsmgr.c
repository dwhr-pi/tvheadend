/*
 *  Digital Video Recorder - file system management
 *  Copyright (C) 2015 Jaroslav Kysela
 *  Copyright (C) 2015 Glenn Christiaensen
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <libgen.h> /* basename */

#include "tvheadend.h"
#include "dvr.h"
#include "atomic.h"
#include "notify.h"

#if ENABLE_ANDROID
#include <sys/vfs.h>
#define statvfs statfs
#define fstatvfs fstatfs
#else
#include <sys/statvfs.h>
#endif

static int dvr_disk_space_config_idx;
static int dvr_disk_space_config_size;
static time_t dvr_disk_space_config_lastdelete;
static int64_t dvr_bfree;
static int64_t dvr_btotal;
static pthread_mutex_t dvr_disk_space_mutex;
static gtimer_t dvr_disk_space_timer;
static tasklet_t dvr_disk_space_tasklet;

/**
 * Cleanup old recordings for this config until the dvr_cleanup_threshold is reached
 * Only "Keep until space needed" recordings are deleted, starting with the oldest one
 */
static int64_t
dvr_disk_space_cleanup(dvr_config_t *cfg)
{
  dvr_entry_t *de, *oldest;
  time_t stoptime;
  int64_t requiredBytes, availBytes;
  int64_t clearedBytes = 0, fileSize;
  unsigned long int filesystemId;
  struct statvfs diskdata;
  struct tm tm;
  int loops = 0;
  char tbuf[64];
  const char *configName;

  if (!cfg || !cfg->dvr_enabled || statvfs(cfg->dvr_storage, &diskdata) == -1)
    return -1;

  filesystemId  = diskdata.f_fsid;
  availBytes    = diskdata.f_bsize * (int64_t)diskdata.f_bavail;
  requiredBytes = (int64_t)cfg->dvr_cleanup_threshold*(int64_t)1024*(int64_t)1024;
  configName    = cfg != dvr_config_find_by_name(NULL) ? cfg->dvr_config_name : "Default profile";

  /* When deleting a file from the disk, the system needs some time to actually do this */
  /* If calling this function to fast after the previous call, statvfs might be wrong/not updated yet */
  /* So we are risking to delete more files than needed, so allow 10s for the system to handle previous deletes */
  if (dvr_disk_space_config_lastdelete + 10 > dispatch_clock) {
    tvhlog(LOG_WARNING, "dvr","disk space cleanup for config \"%s\" is not allowed now", configName);
    return -1;
  }

  if (diskdata.f_bsize * (int64_t)diskdata.f_blocks < requiredBytes) {
    tvhlog(LOG_WARNING, "dvr","disk space cleanup for config \"%s\", required free space \"%ld MB\" is smaller than the total disk size!",
           configName, requiredBytes/(int64_t)1024/(int64_t)1024);
    return -1;
  }

  tvhlog(LOG_INFO, "dvr","disk space cleanup for config \"%s\", required free space \"%ld MB\", current free space \"%ld MB\"",
         configName, requiredBytes/(int64_t)1024/(int64_t)1024, availBytes/(int64_t)1024/(int64_t)1024);

  while (availBytes < requiredBytes) {
    oldest = NULL;
    stoptime = dispatch_clock;

    LIST_FOREACH(de, &dvrentries, de_global_link) {
      if (de->de_sched_state != DVR_COMPLETED &&
          de->de_sched_state != DVR_MISSED_TIME)
        continue;

      if (dvr_entry_get_stop_time(de) > stoptime)
        continue;

      if (dvr_entry_get_removal_days(de) != DVR_RET_SPACENEED) // only remove the allowed ones
        continue;

      if (dvr_get_filename(de) == NULL || dvr_get_filesize(de) <= 0)
        continue;

      if(statvfs(dvr_get_filename(de), &diskdata) == -1)
        continue;

      /* Checking for the same config is useless as it's storage path might be changed meanwhile */
      /* Check for the same file system instead */
      if (filesystemId == 0 || diskdata.f_fsid != filesystemId)
        continue;

      oldest = de; // the oldest one until now
      stoptime = dvr_entry_get_stop_time(de);
    }

    if (oldest) {
      fileSize = dvr_get_filesize(oldest);
      availBytes += fileSize;
      clearedBytes += fileSize;

      localtime_r(&stoptime, &tm);
      if (strftime(tbuf, sizeof(tbuf), "%F %T", &tm) <= 0)
        *tbuf = 0;
      tvhlog(LOG_INFO, "dvr","Delete \"until space needed\" recording \"%s\" with stop time \"%s\" and file size \"%ld MB\"",
             lang_str_get(oldest->de_title, NULL), tbuf, fileSize/(int64_t)1024/(int64_t)1024);

      dvr_disk_space_config_lastdelete = dispatch_clock;
      dvr_entry_delete(oldest, 1);    // delete actual file
      if (dvr_entry_get_retention_days(oldest) == DVR_RET_ONREMOVE)
        dvr_entry_destroy(oldest, 1); // also delete database entry
    } else {
      tvhlog(LOG_WARNING, "dvr", "%s \"until space needed\" recordings found for config \"%s\", you are running out of disk space very soon!",
             loops > 0 ? "Not enough" : "No", configName);
      goto finish;
    }

    loops++;
    if (loops >= 10) {
      tvhlog(LOG_WARNING, "dvr", "Not able to clear the required disk space after deleting %i \"until space needed\" recordings...", loops);
      goto finish;
    }
  }

finish:
  tvhlog(LOG_INFO, "dvr","disk space cleanup for config \"%s\", cleared \"%ld MB\" of disk space, new free disk space \"%ld MB\"",
         configName, clearedBytes/(int64_t)1024/(int64_t)1024, availBytes/(int64_t)1024/(int64_t)1024);

  return clearedBytes;
}

/**
 * Check for each dvr config if the free disk size is below the dvr_cleanup_threshold
 * If so and we are using the dvr config ATM (active recording), we start the cleanup procedure
 */
static void
dvr_disk_space_check()
{
  dvr_config_t *cfg;
  dvr_entry_t *de;
  struct statvfs diskdata;
  int64_t requiredBytes, availBytes;
  int idx = 0, cleanupDone = 0;

  pthread_mutex_lock(&global_lock);

  dvr_disk_space_config_idx++;
  if (dvr_disk_space_config_idx > dvr_disk_space_config_size)
    dvr_disk_space_config_idx = 1;

  LIST_FOREACH(cfg, &dvrconfigs, config_link) {
    idx++;

    if (cfg->dvr_enabled &&
        !cleanupDone &&
        idx >= dvr_disk_space_config_idx &&
        statvfs(cfg->dvr_storage, &diskdata) != -1)
    {
      availBytes = diskdata.f_bsize * (int64_t)diskdata.f_bavail;
      requiredBytes = (int64_t)cfg->dvr_cleanup_threshold*(int64_t)1024*(int64_t)1024;

      if (availBytes < requiredBytes) {
        LIST_FOREACH(de, &dvrentries, de_global_link) {

          /* only start cleanup if we are actually writing files right now */
          if (de->de_sched_state != DVR_RECORDING || !de->de_config || de->de_config != cfg)
            continue;

          tvhlog(LOG_WARNING, "dvr","running out of free disk space for dvr config \"%s\", required free space \"%ld MB\", current free space \"%ld MB\"",
              cfg != dvr_config_find_by_name(NULL) ? cfg->dvr_config_name : "Default profile",
              requiredBytes/(int64_t)1024/(int64_t)1024, availBytes/(int64_t)1024/(int64_t)1024);

          /* only cleanup one directory at the time as the system needs time to delete the actual files */
          dvr_disk_space_cleanup(de->de_config);
          cleanupDone = 1;
          dvr_disk_space_config_idx = idx + 1;
          break;
        }
      }
      else {
        tvhlog(LOG_DEBUG, "dvr","checking free disk space for config \"%s\" : OK",
            cfg != dvr_config_find_by_name(NULL) ? cfg->dvr_config_name : "Default profile");
      }
    }
  }

  if (!cleanupDone)
    dvr_disk_space_config_idx = 0;

  dvr_disk_space_config_size = idx;

  pthread_mutex_unlock(&global_lock);
}

/**
 *
 */
static void
dvr_get_disk_space_update(const char *path)
{
  struct statvfs diskdata;

  if(statvfs(path, &diskdata) == -1)
    return;

  pthread_mutex_lock(&dvr_disk_space_mutex);
  dvr_bfree = diskdata.f_bsize * (int64_t)diskdata.f_bavail;
  dvr_btotal = diskdata.f_bsize * (int64_t)diskdata.f_blocks;
  pthread_mutex_unlock(&dvr_disk_space_mutex);
}

/**
 *
 */
static void
dvr_get_disk_space_tcb(void *opaque, int dearmed)
{
  if (!dearmed) {
    htsmsg_t *m = htsmsg_create_map();

    /* update disk space from default dvr config */
    dvr_get_disk_space_update((char *)opaque);
    htsmsg_add_s64(m, "freediskspace", dvr_bfree);
    htsmsg_add_s64(m, "totaldiskspace", dvr_btotal);
    notify_by_msg("diskspaceUpdate", m, 0);

    /* check free disk space for each dvr config and start cleanup if needed */
    pthread_mutex_unlock(&tasklet_lock);
    dvr_disk_space_check();
    pthread_mutex_lock(&tasklet_lock);
  }

  free(opaque);
}

static void
dvr_get_disk_space_cb(void *aux)
{
  dvr_config_t *cfg;
  char *path;

  lock_assert(&global_lock);

  cfg = dvr_config_find_by_name_default(NULL);
  if (cfg->dvr_storage && cfg->dvr_storage[0]) {
    path = strdup(cfg->dvr_storage);
    tasklet_arm(&dvr_disk_space_tasklet, dvr_get_disk_space_tcb, path);
  }
  gtimer_arm(&dvr_disk_space_timer, dvr_get_disk_space_cb, NULL, 15);
}

/**
 *
 */
void
dvr_disk_space_init(void)
{
  dvr_config_t *cfg = dvr_config_find_by_name_default(NULL);
  pthread_mutex_init(&dvr_disk_space_mutex, NULL);
  dvr_get_disk_space_update(cfg->dvr_storage);
  gtimer_arm(&dvr_disk_space_timer, dvr_get_disk_space_cb, NULL, 5);
}

/**
 *
 */
void
dvr_disk_space_done(void)
{
  tasklet_disarm(&dvr_disk_space_tasklet);
  gtimer_disarm(&dvr_disk_space_timer);
}

/**
 *
 */
int
dvr_get_disk_space(int64_t *bfree, int64_t *btotal)
{
  int res = 0;

  pthread_mutex_lock(&dvr_disk_space_mutex);
  if (dvr_bfree || dvr_btotal) {
    *bfree = dvr_bfree;
    *btotal = dvr_btotal;
  } else {
    res = -EINVAL;
  }
  pthread_mutex_unlock(&dvr_disk_space_mutex);
  return res;
}