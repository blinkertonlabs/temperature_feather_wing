# Temperature Feather Wing
Feather Wing to measure temperature and humidity, while enabling sleep mode on a Feather controller board.

This project is really a mashup of several other existing projects.  
http://www.blinkertonlabs.com/wireless-temperature-monitor.html

The main goals of this Feather Wing are as follows.
* Measure temperature and humidity using a [DHT11 or DHT22](https://learn.adafruit.com/dht) sensor
* Allow for the Feather controller to sleep/wake
* Measure the battery voltage to estimate the remaining power

The DHT sensor was chosen to keep costs down.  
Ideally, a user could distribute one of these sensors in each room of their living space to record how efficiently the heating/cooling energy is being ditribited.  Then, as energy efficientcy changes are made, the user could see the results and track their effectiveness.
