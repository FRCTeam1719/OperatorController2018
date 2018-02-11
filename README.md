# OperatorController2018
FRC Team 1719's operator control station for the 2018 FIRST POWERUP game.

## What it do?
An Arduino Leonardo emulating a controller interfaces with network tables to update the positon of a motorised fader only updating its joystick values when a capacitive tounch sensor is triggered.

## Things Used

* [Arduino Leonardo](https://store.arduino.cc/usa/arduino-leonardo-with-headers) - A HID compatible arduino.
* [Sparkfun Motorised Fader](https://www.sparkfun.com/products/10976) - Motorised fader.
* [Dual TB6612FNG Motor Controller](https://www.sparkfun.com/products/14450) - Motor Controller to control the fader.
* [30mm LED Arcade Button (*6)](https://www.adafruit.com/product/474) - Arcade buttons for operator control.

* [Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary) - Library for emulating HID controller.
* [CapacitiveSensor Library](https://github.com/PaulStoffregen/CapacitiveSensor) - Library for working with the Capacitive Sensor.
* [Uni_Mixer](https://github.com/beausilver/uni_mixer/blob/master/Arduino/uni_mixer/uni_mixer.ino) - Example of using motorised fader.
* [PyNetworkTables](https://github.com/robotpy/pynetworktables) - (Python wrappers for NetworkTables and SmartDashboard);