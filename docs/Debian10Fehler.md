# Debian 10 Kernel compiler Fehler


Quelle: https://debianforum.de/forum/viewtopic.php?t=174285

Nachfolgend ist für AMD 64 Bit Systeme. Nicht für ARM64 geeignet. 
```
apt-get install -y libncurses-dev wget bzip2 make build-essential bc chrpath gawk texinfo libsdl1.2-dev whiptail diffstat cpio libssl-dev flex
```

```
cd ~
mkdir kernel
cd kernel
```

```
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.2.6.tar.xz
tar xvf linux-5.2.6.tar.xz
cd linux-5.2.6
cp /boot/config-`uname -r` .config
```

```
yes "" | make oldconfig

make menuconfig
```

```
make -j16 bzImage modules

make -j16 deb-pkg LOCALVERSION=-Test KDEB_PKGVERSION=1
```

```
```
