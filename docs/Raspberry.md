
# TV Headend mit dem Raspberry Pi

Quelle: https://tvheadend.org/boards/5/topics/10622

Version simple
```
git clone --depth 1 https://github.com/tvheadend/tvheadend.git
./configure
./make
```

Quick & Easy guide to building Tvheadend on a RPi2 (This also works on any other deb system!).
```
sudo apt-get install git build-essential debhelper pkg-config fakeroot
git clone https://github.com/tvheadend/tvheadend.git build/tvheadend/master
cd build/tvheadend/master
```
##### If you do not want unstable run the following line #####
```
git checkout release/4.0
```
##### If you do not want unstable run the above line #####
```
AUTOBUILD_CONFIGURE_EXTRA=--enable-hdhomerun_client\ --enable-ffmpeg_static\ --disable-bintray_cache ./Autobuild.sh
```

What each lines does.
* 1 Installs a few dependencies (you'll need to install some more later on).
* 2 Clones the Tvheadend master branch from github & places it in build/tvheadend/master.
* 3 Changes directory to the above path.
* 4 (optional) changes source to release/4.0.
* 5 Runs the Autobuild script that will build a debian package so that you can install it in a nice and neat way.

You can pass more options to AUTOBUILD_CONFIGURE_EXTRA just make sure to place an escaped space between each option, e.g.

```
AUTOBUILD_CONFIGURE_EXTRA=--enable-hdhomerun_client\ --disable-ffmpeg_static ./Autobuild.sh
```

A list of build options can be found by running (in the source directory).

Note that the Raspberry Pi is not powerful enough to do transcoding via the cpu, disabling ffmpeg during your build will reduce the time needed to build..

```
./configure --help
```

The Autobuild.sh script will complain about other missing dependencies you need to install those, e.g.

```
sudo apt-get install libcurl14-gnutls-dev liburiparser-dev
```

Run the script again.

Once the build has completed you'll find the built debian package (E.g tvheadend_4.1-368~geeda7d7_armhf.deb) in build/tvheadend.

You can then install it (and the debug package) using.

```
cd build/tvheadend
sudo dpkg -i tvheadend*.deb
```

You may need to do the following on some systems with systemd, if the service doesn't start after install.

```
sudo systemctl disable tvheadend
sudo systemctl enable tvheadend
sudo systemctl start tvheadend
```






Quelle: https://gist.github.com/dadosch/23a895f99b41ef95d4e57926bcf34e41

# TV Headend with Raspberry Pi
```
apt-get update
apt-get install gcc-4.9 g++-4.9 build-essential
apt-get install unzip git-core pkg-config dvb-apps gettext
apt-get install libcurl4-openssl-dev libssl-dev libavahi-client-dev zlib1g-dev libavcodec-dev libavutil-dev libavformat-dev libswscale-dev
export CC=gcc-4.9
export GCC=gcc-4.9
git clone https://github.com/tvheadend/tvheadend
cd tvheadend
./configure
make -j4
make install
groupadd tvheadend
useradd -g tvheadend -G video,audio -m tvheadend
```

## Firmware for 0572:6831.md

Download https://github.com/OpenELEC/dvb-firmware/blob/master/firmware/dvb-demod-m88ds3103.fw to folder /lib/firmware

## init.d File.md

```
#!/bin/bash
### BEGIN INIT INFO
# Provides:          tvheadend
# Required-Start:    $local_fs $remote_fs $network
# Required-Stop:     $local_fs $remote_fs $network
# Should-Start:      $syslog
# Should-Stop:       $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1
# Short-Description: start/stop tvheadend Server
### END INIT INFO

TVHNAME="tvheadend"
TVHBIN="/usr/local/bin/tvheadend"
TVHUSER="tvheadend"
TVHGROUP="tvheadend"
PIDFILE=/var/run/$TVHNAME.pid

start() {
    if [ -e $PIDFILE ]; then
        PID=$(ps ax | grep -v grep | grep -w $(cat $PIDFILE) | awk '{print $1}')
        if [ -n "$PID" ]; then
            echo "$TVHNAME already running (pid $PID)."
            exit 1
        fi
    fi
    echo -n "Starting $TVHNAME: "
    start-stop-daemon --start --background --pidfile $PIDFILE --make-pidfile --user ${TVHUSER} --exec ${TVHBIN} -- \
        -u ${TVHUSER} -g ${TVHGROUP} -f -C
    echo "Done."
}

stop() {
    if [ -e $PIDFILE ]; then
        PID=$(ps ax | grep -v grep | grep -w $(cat $PIDFILE) | awk '{print $1}')
        if [ -n "$PID" ]; then
            echo -n "Stopping $TVHNAME: "
            start-stop-daemon --stop --quiet --pidfile $PIDFILE --name ${TVHNAME}
            echo "Done."
        else
            echo "$TVHNAME is not running."
        fi
    else
        echo "$TVHNAME is not running."
    fi
}

status() {
    if [ -e $PIDFILE ]; then
        PID=$(ps ax | grep -v grep | grep -w $(cat $PIDFILE) | awk '{print $1}')
        if [ -n "$PID" ]; then
            echo "$TVHNAME is running (pid $PID)."
        else
            echo "$TVHNAME is not running."
            [ -e $PIDFILE ] && exit 1 || exit 3
        fi
    fi
}

case "$1" in
    start) start ;;
    stop) stop ;;
    status) status ;;
    restart) stop && sleep 2 && start ;;
    *) echo "Usage: $0 [start|stop|restart|status]" && exit 1 ;;
esac

exit 0
===============
chmod +x /etc/init.d/tvheadend
update-rc.d tvheadend defaults
```


