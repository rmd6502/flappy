flappy
======

This is the source folder for the Flappy Bird in a Box project.

Contents
--------

**circuit** Eagle files

**flappy_final_v8** Not really the final version, but the final version before github

**Arduino** Modifications for the stock Arduino 1.0.5 to enable compiling for the Flappy board.

Installation Instructions
-------------------------

* Install the [Arduino](http://arduino.cc) 1.0.5 IDE.
* Copy the libraries and hardware directories into the sketchbook directory for your platform
  * C:\Documents and Settings\My Documents\Arduino
  * ${HOME}/sketchbook
  * ${HOME}/Documents/Arduino
* Install the latest avr-gcc toolchain
  * AVR Studio from [Atmel](http://www.atmel.com) if you're on Windows,
  * sudo apt-get install avr-gcc
  * [Crosspack AVR for Mac](http://www.obdev.at/products/crosspack/index.html)
* Go to the Arduino install directory
  * C:\Program Files(x86)\Arduino
  * Not sure for linux - /usr/local/Arduino?
  * /Applications/Arduino.app
* Find the hardware/tools subdirectory
* mv the avr directory to e.g. avr.save - this is an old version of the toolchain that seems to 
have problems
* Copy or link the root of your newest toolchain as 'avr' in the hardware/tools directory.
* Restart the Arduino IDE
* You should be able to choose Flappy Board as your board type, and Dragon ISP as the programmer
* Choose "upload using programmer" instead of Upload
