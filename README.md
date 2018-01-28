# esp32_led_strip
Driving a 12V RGB Strip using the ESP32's MCPWM component

Author: Mike Field <hamster@snap.net.nz>

This design generates PWM signals on GPIO pins 25, 26, and 27, that can be used
to drive MOSFETs to control 'dumb' RGB LED strips (opposed to inteligent LEDs).

I used the SI4944DY SOIC8 DUAL MOSFET that was available easily from Jaycar (an
AU/NZ hobby electronics store. The signals drive the MOSFET Gates through 1k ohm
resisters, The source is connected to GND, and the strip connected to the drain,
as the strip I used has a common annode. These MOSFETs are rated to 5A, way more
than the strip I used needed (about 1.5A max).

Video of it in action is at https://youtu.be/g-KZkL_qF9g