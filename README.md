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

tvheadend dvb-t2 germany
-------------------
* https://www.google.com/search?q=tvheadend+dvb-t2+germany&oq=tvheadend+dvb-t2+&aqs=chrome.3.69i57j0i512j0i22i30l8.12408j0j4&sourceid=chrome&ie=UTF-8
* https://buyzero.de/blogs/news/raspberry-pi-dvb-tv-hat-tv-headend-dvb-t2-in-deutschland-einrichten
* https://tvheadend.org/boards/4/topics/21148

raspberry pi h 265 codec
-------------------
* https://www.google.com/search?q=raspberry+pi+h+265+codec&oq=raspberry+pi+h.265+&aqs=chrome.3.69i57j0i22i30l7j0i10i22i30j0i22i30.20796j0j7&sourceid=chrome&ie=UTF-8
* https://www.areadvd.de/news/neuer-raspberry-pi-4-mit-4k-hevc-decoder/
* https://github.com/moonlight-stream/moonlight-qt/issues/409
* https://forums.raspberrypi.com/viewtopic.php?t=308554
 
Das originale neue Raspberry Pi OS Bullseye soll dies schon von Hause seit 11/2021 aus können und kann angeblich 4k Videos auf einem Pi 4b 8G ruckelfrei wiedergeben.  
* https://www.raspberrypi.com/documentation/accessories/camera.html

tvheadend iptv
-------------------
* https://www.google.com/search?q=tvheadend+iptv&oq=tvheadend+iptv&aqs=chrome..69i57j69i65j69i60.3857j0j4&sourceid=chrome&ie=UTF-8


Livestreams
tvheadend iptv facebook youtube
-------------------
* https://www.google.com/search?q=tvheadend+iptv+facebook+youtube&source=lmns&bih=912&biw=1302&hl=de&sa=X&ved=2ahUKEwi-5fOKp4n1AhVMO-wKHbbdAY4Q_AUoAHoECAEQAA
* https://www.reddit.com/r/Streamlink/comments/l2nc6n/guide_how_to_turn_livestreams_from_any_major/
* https://tvheadend.org/boards/4/topics/43493?r=43567
* https://cgomesu.com/blog/Tvhlink/
* https://cgomesu.com/blog/Youtube-as-IPTV-with-TVH/

tvheadend einrichten sat>ip
-------------------
* https://www.google.com/search?q=tvheadend+einrichten+sat%3Eip&oq=tvheadend+einrichten+sat%3Eip&aqs=chrome..69i57j0i512j0i22i30.1171j0j4&sourceid=chrome&ie=UTF-8

Meine Installation
-------------------
Auf einem Raspberry Pi Zero, mit einem Raspberry TVheadend habe ich die TVheadEnd auf ein 32 bit ARM6 Betriebssystem Variante von DietPI's Debian Bullseye versucht zu installieren. 
Leider oft ohne Erfolg! Doch hiermit gelang es mir, die "HTS Tvheadend 4.3-1979~g8fc2dfa7e" endlich und funktionierend hinzubekommen.

Quelle: https://tvheadend.org/projects/tvheadend/wiki/AptRepositories

bei Usage
Weil es oft fehlgeschlagen ist, die Datei im Verzeichniss etc/apt/sources.list.d/tvheadend.list wieder löschen und dann sudo apt-get update und eine andere Version von tvheadend mal versuchen. 
Oder diese Datei mal tvheadend.list manuell bearbeiten. 
Denn die von TVheadEnd bezeichnete Version für Buster ist auf deren Server nicht existend, also musste ich Strech nehmen. 

Fehlerursache das die deb nicht signiert ist, siehe hier:
* https://www.google.com/search?q=debian+apt+nicht+signierte+installieren&oq=debian+apt+nicht+signierte+installieren&aqs=chrome..69i57j0i333.22622j0j7&sourceid=chrome&ie=UTF-8
* https://www.heise.de/tipps-tricks/DEB-in-Debian-Systemen-installieren-so-klappt-s-4926444.html



Diese nachfolgende Anleitung ab hier brachte den erwünschten Erfolgt!  
Vorheriges brauch nicht unbedingt beachtet zu werden.

Schritt 1.
sudo apt-get -y install coreutils wget apt-transport-https lsb-release ca-certificates
Ich habe bei mir den Super User-Mode auf den "root"-Benutzer gesetzt/gelegt und ist mit entscheidend wie sie sich in den Raspberry gewöhnlich einloggen, um damit auch TVheadend zu starten. 
apt-get install sudo; usermod -aG sudo root


Nachfolgend wird der Publickey mit diesem Befehl bekannt gegeben und sollte der gleiche sein, wie bei "Anschließend den zuvorgenannten Key" schon der Key von mir mit eingearbeitet worden ist. 
```
wget -qO- https://doozer.io/keys/tvheadend/tvheadend/pgp | sudo tee /etc/apt/trusted.gpg.d/tvheadend.asc
```
Anschließend den zuvorgenannten Key hier mit einfügen, wie in meinem Beispiel oder mein Beispiel dazu verwenden und die Enter/Eingabetaste drücken. 
```
sudo wget -qO- https://doozer.io/keys/tvheadend/tvheadend/pgp | sudo apt-key add mQENBFrG/QIBCAC9tQeA0NRCQtu7vG1bBmWJCbsrfmo2lELhnsvUvZSG6C31aVhaVI5+I59rWDKjs4v30f7oGvlLgnRGjElP4+aHmVR53v8s3VCBmNkCO64lGc5Kv05RMsdiXRgCbj4Xzl6gwRbfPZngFta2SusPp0aBPrjqlH0ZEnqa5jFDhE6sVkJLTQXwTGGHGIWg6AL0WqkW/o6+iHTbg+qsW93Ij5FvzB09PNKw9a6i+QZiXK9fvE0qJbKBC0J2jReZjyi7nkyd2rOzkhyuz7xux1wIGn7oXSqusey/VFbTUAiZbVuScIW+rY+JV2HNCQlXLdkMP5aiaXGiLeeF8OFz8qNxwPudABEBAAG0JWh0dHBzOi8vZG9vemVyLmlvL3R2aGVhZGVuZC90dmhlYWRlbmSJAR8EEwEIAAkFAlrG/QICGwMACgkQiZQqrlzqoXRfFggARMKrW7K046ivtG8kIXB9RUCdWFOOCSn2ss2F9hcw8b4ro3mSMqlveVvm3myrA59MwoDpHMTONwe4ODCo89dtF0NlTEM2E6v//qHfVwBBjAJhg7eybuPfNZkkqiRUvMioQjef7tTyFX65U7IUpQjKpk+VyrksvTs4oRWwIuNJe7iIIEOTCsnXNYYaNj3SRXOP5Atf+A4O6yOm5kmveURVkVUb/Ta1MT+nv1B/fvQdHGyIRfw7aB4OEtGe6sJn6+BK6AFVb7Q8E1m+PsuxYGzKQNCk/Ed/XTuTwKno8DdPMpmVt0BkN7xrOGLn1A6k4rVeNilFOy1/x2NsQXkVLOWGWw===ruJb
```

Das deb wird mit dem Befehl nachfolgend als tvheadend.list-Textdatei in dem Verzeichniss "`/etc/apt/sources.list.d/`" mit hinzufügen. Mit dieser Datei hatte ich wegen der unterschiedlichen zuvor versuchten Verionen von TVheadEnd massive Probleme bekommen, siehe oben angegeben. Dies nachfolgende hier funktioniert aber, wenn Sie diese vorherige Datei nicht schon wie bei mir existiert hatte und somit eine echte Neu- und Erstinstallation es bei Ihnen ist. 
```
echo "deb http://apt.tvheadend.org/unstable xenial main" | sudo tee -a /etc/apt/sources.list.d/tvheadend.list

echo "deb http://apt.tvheadend.org/unstable raspbian-stretch main" | sudo tee -a /etc/apt/sources.list.d/tvheadend.list
sudo apt-get update
sudo apt-get install tvheadend
```
Mit "J" beantworten und es startet von selbst im blauen Menü der Einrichtungsassist von TVheadEnd. 

Falls bei der Ersteinrichtung von TVheadEnd etwas schiefgelaufen ist, kann mit: 
```
sudo dpkg-reconfigure tvheadend
```
dies korrigiert werden. 
Oder wenn Sie die Konfiguration vollständig entfernen möchten, verwenden Sie Ihren Paketmanager mit --purge option, z.B.: apt-get remove --purge tvheadend*     

Nachfolgend wird hiermit TVheadEnd wieder erneut gestartet, falls TVheadEnd nicht von selbst startete. 
sudo service tvheadend restart

Entweder unter der eigenen IP des Raspberrys (In Ihrem Router z.B. Fritzbox steht die IP Adresse Ihres Netzwerkgeräts): 
http://192.168.178.15:9981

oder mit dem Hostnamen kann man das Controlpanal von TVheadEnd endlich starten. 
http://dietpi:9981

Im Raspberry selbst kann man auch im Browser z.B. Firefox mit 
http://localhost:9981 
versuchen, falls dies leichter ist. Oder vorherig Probleme auftauchten. 

## Manuelle Installation
Quelle: https://wiki.ubuntuusers.de/Tvheadend/


Hinweis!
Fremdsoftware kann das System gefährden.

Gerade da die Version in den Paketquellen oft veraltet ist, ist es ratsam, Tvheadend manuell zu kompilieren.

build-essential
* git
* pkg-config
* libssl-dev
* bzip2
* wget
* libavahi-client-dev
* zlib1g-dev
* libavcodec-dev (universe)
* libavutil-dev (universe)
* libavformat-dev (universe)
* libswscale-dev (universe)
* libavresample-dev (universe)
* dvb-apps (universe)

Befehl zum Installieren der Pakete:
```
sudo apt-get install build-essential git pkg-config libssl-dev bzip2 wget libavahi-client-dev zlib1g-dev libavcodec-dev libavutil-dev libavformat-dev libswscale-dev libavresample-dev dvb-apps 
```
Oder mit apturl installieren, Link: 
apt://build-essential,git,pkg-config,libssl-dev,bzip2,wget,libavahi-client-dev,zlib1g-dev,libavcodec-dev,libavutil-dev,libavformat-dev,libswscale-dev,libavresample-dev,dvb-apps

Anschließend kann die aktuellste Version von Github geholt werden und das Programm kompiliert und installiert werden:

```
git clone https://github.com/tvheadend/tvheadend.git
make
sudo make install 
```

Wichtig ist bei der manuellen Installation außerdem, ein entsprechendes Start-Skript zu erstellen.


## apturl
Installation
Üblicherweise ist apturl in der Standardinstallation enthalten, kann aber auch – wie bei Xubuntu oder Lubuntu – fehlen. Es wird dann über den folgenden Befehl nachinstalliert [1]:

```
sudo apt-get install apturl 
```

Oder mit apturl installieren, Link: 
```
apt://tvheadend
```
Während der Installation wird für die Tvheadend-eigene Benutzerverwaltung ein Administrator angelegt. Dies kann auch nach der Installation geändert werden mittels

TVheadEnd konfigurieren
-------------------
TVheadEnd konfigurieren 
https://www.minipctv.de/tvheadendserver/tvheadend-konfigurieren/

Problemlösungen werden hier beschrieben.
https://www.siski.de/~carsten/tvheadend.html

Intressante Anleitung und Compilierungsanweiungen. 
https://wiki.ubuntuusers.de/Tvheadend/

IPTV setup für Neulinge instressant ist dabei Webgrab++
https://tvheadend.org/boards/4/topics/30601?r=30876

IPTV setup
https://www.matthuisman.nz/2017/06/libreelec-tvheadend-iptv-freeview-nz.html

Konfigutration von TVheadEnd
https://blog.helmutkarger.de/raspberry-media-center-teil-9-tvheadend/

https://www.electronic-research.de/tvheadend-iptv-kabel-sattv-und-epg.html

TVheadEnd 
https://www.google.com/search?q=TVheadEnd&oq=TVheadEnd&aqs=chrome..69i57j69i59l2j69i60l4j69i65.4466j0j7&sourceid=chrome&ie=UTF-8
TVheadEnd einrichten 
https://www.google.com/search?q=tvheadend+einrichten&oq=TVheadEnd+einrichten+&aqs=chrome..69i57j0i512j0i22i30l8.16501j0j7&sourceid=chrome&ie=UTF-8

No assigned adapters
https://www.google.com/search?q=No+assigned+adapters&oq=No+assigned+adapters&aqs=chrome..69i57.103586392j0j0&sourceid=chrome&ie=UTF-8
