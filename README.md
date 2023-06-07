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

**The image below show the finished device**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/711ddc9b-9fa8-4d0b-8114-1899c1d02d32)

**The image below shows the interior of the constructed device**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/ad316e11-c13e-467c-95bb-8ab74c511d78)

**The image below presents the diagram according to which the device has been assembled**

![image](https://github.com/bialowasdominik/fleet-monitor-localisator/assets/106835786/3b3b9ac6-47f8-47c5-9f53-ac7b3f4b9330)




