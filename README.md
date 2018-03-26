# devwatcher
devwatcher observes serial device connections and provides a fixed link (mount point) to that device, regardless of the actual device name (e.g. /dev/ttyUSB0..99 or /dev/ttyACM0..99).

Copyright (C) 2018 Andreas Gollsch

This program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are welcome to redistribute it under certain conditions.

May you have the same problem like me, while writing Arduino programs and the Arduino is connect and communicate with a Linux host, but the device name is not fix to one specific name like ttyUSB0.

Serial devices that are connect via USB will normally appear as ttyUSBx or ttyACMx (depending on USB controllers) on Linux systems. 

If there are more than one device then they will named in order of detection or connection (e.g. ttyUSB0, ttyUSB1 …).

In that fact, it is not ensure which USB device is your Arduino project. Therefore, every time you connect a serial device you have to verify which device name is assign to your serial device.

Here comes my project that observes the /dev folder for new TTY connection and tries to identify the devices and creates a fixed symbolic link to TTY-name.

That needs some modification to your program to tell devwatcher what symbolic link (mount point) you do prefer as fixed device name (e.g. /dev/my-arduino-project).

*	The baud rate is restricted to 115200 Baud
*	The first output on your device should be “MountPoint:<Symbolic Link>”
  
Following this points, devwatcher will create the symbolic link always when serial device will be connected to Linux host and remove symbolic link when the serial device will be disconnected.

## Build
* Download and install Qt5 from [www.qt.io/download](https://www.qt.io/download)
* Download this repository
* open a terminal and switch into devwatcher folder
* Run ```qmake```
* Build project with ```make```

## Run
Start program with ```sudo ./devwatcher```

## License
This project is licensed under GNU GPL - see [LICENSE](LICENSE) for
details
