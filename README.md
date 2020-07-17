A simple i2c slave that read analog and digital inputs for a joystick hardware (to be pulled for a master like a raspberry pi). You can build only the AVR CI and some components to a low footprint …

My idea is connect the raspberry pi with i2c channel to arduino uno or leonardo and implement a polling for values of joystick movements in x and y axis and a press event of the  joystick's z axis button of.

RPI 3 and Uno
+---------------------+             +---------------+    +-----------+
| raspbarry pi 3     3|--i2c-SDA----|A4 Arduino   A0|----|x  joystick|
|                    5|--i2c-SCL----|A5   Uno     A1|----|y          |
|                   20|--GND--------|GND          D7|----|sw button  |
+---------------------+             +---------------+    +-----------+

RPI 3 and Leonardo
+---------------------+             +---------------+    +-----------+
| raspbarry pi 3     3|--i2c-SDA----|D2 Arduino   A0|----|x  joystick|
|                    5|--i2c-SCL----|D3 Leonardo  A1|----|y          |
|                   20|--GND--------|GND          D7|----|sw button  |
+---------------------+             +---------------+    +-----------+

You can take the raspbarry's pinout of on internet :-)
(https://docs.microsoft.com/pt-br/windows/iot-core/media/pinmappingsrpi/rp2_pinout.png)
