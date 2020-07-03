A simple i2c slave that read analog and digital inputs for a joystick hardware (to be pulled for a master like a raspberry pi). You can build only the AVR CI and some components to a low footprint …

My idea is connect the raspberry pi with i2c channel to arduino uno or leonardo and implement a polling for values of joystick movements in x and y axis and a press event of the  joystick's z axis button of.


+-------------+            +-------------+    +-----------+
| raspbarry pi|---<i2c>----| Arduino   A0|----|x  joystick|
+-------------+            |           A1|----|y          |
                           |           D2|----|sw button  |
                           +-------------+    +-----------+

