# MCU Firmware Development

__All commands in this guide require `root` access, except when stated otherwise.__

## Environment

  * Ubuntu 15.04
  * Atom v1.7.x

## Prepare Operating System

### Install Required Software

```
apt-get install build-essential clang
pip install platformio
```

### Serial Port Permissions
Create a new file `/etc/udev/rules.d/90-arduino.rules`, insert the following lines & replace `<username>` with your user.

```
KERNEL="ttyUSB[0-9]*", TAG+="udev-acl", TAG+="uaccess", OWNER="<username>"
KERNEL="ttyACM[0-9]*", TAG+="udev-acl", TAG+="uaccess", OWNER="<username>"
```

Add your user to the `tty` & `dialout` groups.

```
usermod -a -G tty <username>
usermod -a -G dialout <username>
apt-get remove modemmanager
```

### JTAG/ICSP Programmers (Optional)
Create a new file `/etc/udev/rules.d/avrisp.rules` and insert the following lines;

```
SUBSYSTEM!="usb_device", ACTION!="add", GOTO="avrisp_end"

# Atmel Corp. JTAG ICE mkII
ATTR{idVendor}=="03eb", ATTRS{idProduct}=="2103", MODE="660", GROUP="dialout"
# Atmel Corp. AVRISP mkII
ATTR{idVendor}=="03eb", ATTRS{idProduct}=="2104", MODE="660", GROUP="dialout"
# Atmel Corp. Dragon
ATTR{idVendor}=="03eb", ATTRS{idProduct}=="2107", MODE="660", GROUP="dialout"

LABEL="avrisp_end"
```

### Apply udev Rules

```
udevadm control --reload-rules
udevadm trigger
```

## Setup Atom

  1. Download and install Atom `wget https://atom.io/download/deb && sudo dpkg -i atom-amd64.deb`
  1. Open Atom and press `ctrl-,` and install the `platformio-ide` & `platomformio`
  1. Open a new Terminal, type `echo $PATH` and paste the result into the `platomformio` settings

## Create a Project

```
mkdir my-project
cd my-project/
platformio init --board=<name>
atom .
```
