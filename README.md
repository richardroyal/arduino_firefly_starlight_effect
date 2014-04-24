## Simple Firefly / Starlight Effect with LED Grid

### Materials

* TLC5940 16-Channel LED Driver IC 
* [TLC5940 Auduino Library](https://code.google.com/p/tlc5940arduino/)
* Arduino Uno
* Wire kit with resistors

### Setup

* Install TLC5940 Library as described [here](http://playground.arduino.cc/Learning/TLC5940).

* Setup hardware as followed ![Schematic for Arduino and TLC59540](https://raw.githubusercontent.com/richardroyal/arduino_firefly_starlight_effect/master/breadboard-arduino-tlc5940.png)

* Open [Sketch](https://github.com/richardroyal/arduino_firefly_starlight_effect/blob/master/firefly_starlight/firefly_starlight.ino) from project repo and push to Arduino using IDE.

### Testing with LED

Arduino Uno comes equipped with test LED on PIN 13 that can be used to demonstrate effect.

Load up [test sketch](https://github.com/richardroyal/arduino_firefly_starlight_effect/blob/master/firefly_starlight_test/firefly_starlight_test.ino) and play with constants to see effect.
