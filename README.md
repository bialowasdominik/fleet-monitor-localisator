# Fleet monitor
>Device

Part of the system that was the subject of my engineering thesis. 

The GPS locator, which is part of the fleet monitor system, allows for recording vehicle positions and sending them to the server using the HTTP protocol. The device can be easily installed in the vehicle and powered by a 12V voltage.
The device has been designed and implemented based on the following technologies and components:

**Technologies**
- C++ (language)
- TinyGPSPlus (library)
- SoftwareSerial (library)

**Components**
- Arduino Nano
- LCD 2x16
- I2C module for LCD display
- GPS GY-NEO6M
- SIM800 (GSM/GPRS communication)
- Step-down converter (from 12v to 4V)
- DC socket (for power supply)
- Kradex Z4 (case to mount all components)

**The image below show the finished device.**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/70df97c2-0d89-4656-a609-06f8bd354920)

**The image below shows the interior of the constructed device**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/9d0f830a-1ae0-4144-b59f-789be496e371)

**The image below presents the diagram according to which the device has been assembled**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/bfe96c46-69a9-4ba8-9c00-c36ee288dfaf)


