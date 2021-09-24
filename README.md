![TVHeadend Logo](https://github.com/tvheadend/tvheadend/raw/master/src/webui/static/img/satip-icon120.png)
Tvheadend
========================================
(c) 2006 - 2021 Tvheadend Foundation CIC

Status
------

[![Build Status](https://travis-ci.org/tvheadend/tvheadend.svg?branch=master)](https://travis-ci.org/tvheadend/tvheadend)
[![Coverity Scan](https://scan.coverity.com/projects/2114/badge.svg)](https://scan.coverity.com/projects/2114)
[![Github last commit](https://img.shields.io/github/last-commit/tvheadend/tvheadend)](https://github.com/tvheadend/tvheadend)

[![Releases](https://img.shields.io/github/tag/tvheadend/tvheadend.svg?style=flat-square)](https://github.com/tvheadend/tvheadend/releases)
[![License](https://img.shields.io/badge/license-GPLv3-blue)](./LICENSE.md) 
[![GitHub Activity](https://img.shields.io/github/commit-activity/y/tvheadend/tvheadend.svg?label=commits)](https://github.com/tvheadend/tvheadend/commits)


What it is
----------

![tvheadend front page](https://github.com/tvheadend/tvheadend/raw/master/src/webui/static/img/epg.png)

Tvheadend is a TV streaming server and digital video recorder.

It supports the following inputs:

  * DVB-C(2)
  * DVB-T(2)
  * DVB-S(2)
  * ATSC
  * SAT>IP
  * HDHomeRun
  * IPTV
    * UDP
    * HTTP

It supports the following outputs:

  * HTTP
  * HTSP (own protocol)
  * SAT>IP

How to build for Linux
----------------------

First you need to configure:

	$ ./configure

If any dependencies are missing the configure script will complain or attempt
to disable optional features.

Build the binary:

	$ make

After build, the binary resides in `build.linux` directory.

Thus, to start it, just type:

	$ ./build.linux/tvheadend

Settings are stored in `$HOME/.hts/tvheadend`.

How to build for OS X
---------------------

Same build procedure applies to OS X.
After build, the binary resides in `build.darwin` directory.

Only network sources (IPTV, SAT>IP) are supported on OS X.
There is no support for DVB USB sticks and PCI cards.
Transcoding is currently not supported.

Packages
--------

Install instructions for various distributions can be found at the [Wiki](https://tvheadend.org/projects/tvheadend/wiki/Download).

Further information
-------------------

For more information about building, including generating packages, please visit:
* https://tvheadend.org/projects/tvheadend/wiki/Building
* https://tvheadend.org/projects/tvheadend/wiki/Packaging
* https://tvheadend.org/projects/tvheadend/wiki/Git
* https://tvheadend.org/projects/tvheadend/wiki/Internationalization


Weitere Informationen
-------------------
* https://tvheadend.org/projects/tvheadend/wiki/AptRepositories
* https://www.minipctv.de/tvheadendserver/tvheadend-auf-dem-raspberrypi-installieren/
* http://raspberry.tips/raspberrypi-tutorials/raspberry-pi-live-fernsehen-mit-tvheadend
* https://canox.net/2021/01/tvheadend-unter-raspberry-pi-os-installieren/
* https://technikkram.net/blog/2018/01/30/tv-server-auf-dem-rasplerry-pi-ein-tutorial-fuer-alle-fernseh-freunde/
* https://pimylifeup.com/raspberry-pi-tvheadend/

Weitere Informationen auf YouTube
-------------------
* https://www.youtube.com/watch?v=mZuCIHWR8Vg
* https://www.youtube.com/watch?v=1TS-Z04toA4
* https://www.youtube.com/watch?v=d2aMYLHD2PQ


Meine Installation
-------------------
Quelle: https://tvheadend.org/projects/tvheadend/wiki/AptRepositories

bei Usage
sudo apt-get -y install coreutils wget apt-transport-https lsb-release ca-certificates
echo "deb http://apt.tvheadend.org/stable raspbian-stretch main" | sudo tee -a /etc/apt/sources.list.d/tvheadend.list
sudo apt-get update

Ich erhielt folgende Fehlermeldung
W: GPG-Fehler: http://apt.tvheadend.org/stable raspbian-stretch Release: Die folgenden Signaturen konnten nicht überprüft werden, weil ihr öffentlicher Schlüssel nicht verfügbar ist: NO_PUBKEY 89942AAE5CEAA174
E: Das Depot »http://apt.tvheadend.org/stable raspbian-stretch Release« ist nicht signiert.
N: Eine Aktualisierung von solch einem Depot kann nicht auf eine sichere Art durchgeführt werden, daher ist es standardmäßig deaktiviert.
N: Weitere Details zur Erzeugung von Paketdepots sowie zu deren Benutzerkonfiguration finden Sie in der Handbuchseite apt-secure(8).

weiter ging es mit:
sudo apt-get install tvheadend
leider war ab hier schluss...
E: Paket tvheadend kann nicht gefunden werden.

sudo dpkg-reconfigure tvheadend
sudo service tvheadend restart



