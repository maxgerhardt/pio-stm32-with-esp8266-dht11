# STM32 + ESP8266 IoT demo using PlatformIO

## What is this project?

- a Bluepill board (STM32F103C8) reads out a DHT11 temperature and humidity sensor. 
- it transmits the values via its UART2 to the RX of the ESP8266 as a simple text string, e.g. "23,40" 
- the ESP8266 connects to a WiFi network and pushes the data to a ThingSpeak.com channel of your choice 

## Pinout

- Bluepill 
	- power (3.3V + GND)
	- DHT11 data pin to PA0
	- USART2 TX (PA2) to the RX pin (GPIO3) of the ESP8266
- ESP8266
	- power (e.g. via USB cable for the NodeMCU)
	- common GND with the STM32 board 
	- RX pin to STM32's TX pin as described above 
	

## Settings 

- ESP8266 (`settings.h`)
	- `SECRET_SSID`, `SECRET_PASS`: place your WiFi SSID and password here 
	- `SECRET_CH_ID`, `SECRET_WRITE_APIKEY`: place your channel ID and write API key from ThingSpeak here
- STM32
	- no changable macros

## Setup re-creation 

Sign up for a thingspeak.com account, create a new channel and add two fields to it. Call them "Temperature" and "Humidity". 

Format the graphs in the private view as much as you like, e.g. with °C on the y axis on time on the x axis.

Copy your "Channel ID: XXXXX" and "Write API Key" (in "API Keys") to the `.h` file as described above. Also put your correct WiFi credentials in there.

## Media 

![thingspeak](thingspeak_channel.png)

