# OperatorController2018
FRC Team 1719's operator control station for the 2018 FIRST POWERUP game.

## What it do?
An Arduino Leonardo emulating a controller interfaces with network tables to update the position of a motorized fader only updating its joystick values when a capacitive touch sensor is triggered.

## Physical Things Used

* [Arduino Leonardo](https://store.arduino.cc/usa/arduino-leonardo-with-headers) - A HID compatible arduino.
* [Sparkfun Motorized Fader](https://www.sparkfun.com/products/10976) - motorized fader.
* [Dual TB6612FNG Motor Controller](https://www.sparkfun.com/products/14450) - Motor Controller to control the fader.
* [30mm LED Arcade Button (*6)](https://www.adafruit.com/product/474) - Arcade buttons for operator control.

## Digital Things Used
* [Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary) - Library for emulating HID controller.
* [CapacitiveSensor Library](https://github.com/PaulStoffregen/CapacitiveSensor) - Library for working with the Capacitive Sensor.
* [PyNetworkTables](https://github.com/robotpy/pynetworktables) - Python wrappers for NetworkTables and SmartDashboard.
* [PySerial](https://github.com/pyserial/pyserial) - Python serial port access library

## Other Examples
* [Uni_Mixer](https://github.com/beausilver/uni_mixer/) - Example of using motorized fader.
* [Python Arduino Example](https://github.com/headrotor/Python-Arduino-example/) - example of python interfacing with an Arduino.
* [Serial Communication between Raspberry Pi & Arduino](https://classes.engineering.wustl.edu/ese205/core/index.php?title=Serial_Communication_between_Raspberry_Pi_%26_Arduino) - WUSTL engineering example of using pyserial.