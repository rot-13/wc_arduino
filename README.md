# WC Arduino
WC occupancy detector Arduino code.

This repo holds the Arduino "sketch" code used on the Arduino chip. The hardware we used is a [Huzzah Feather ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide) chip, and the code may be highly customizable for this specific chip.

## Installation

1. Follow instructions on [Huzzah Feather ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide) to get your dev environment running
1. Edit `wifi_credentials.h` in this repo with the correct wifi netword name (SSID) and password
1. Install the code in this project onto an Arduino
1. Connect a push button to the 12 & GND (ground) pins of the arduino chip (button "A"), and another button to the 14 & GND pins (button "B"). Press and hold any button to issue a server call and turn the in board led light on. 
