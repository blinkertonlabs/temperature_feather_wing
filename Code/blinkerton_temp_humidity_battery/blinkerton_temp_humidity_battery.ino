// Adafruit IO Temperature & Humidity Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/* **********************************************************************************************
 * Blinkerton Labs Contribution
 * 03/2019
 * 
 * To get to work, had to change the sensor type from a DHT22 to DHT11 to match the installed sensor
 * 
 * HUZZAH Board
 * https://www.adafruit.com/product/2821
 * 
 * 
 * The majority of the code shown below comes from the following tutorial.
 * https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity
 * 
 * 
 * Good reference on measuring the battery level.
 * https://learn.adafruit.com/using-ifttt-with-adafruit-io?view=all
 * https://github.com/adafruit/Adafruit_Learning_System_Guides/tree/master/IFTTT_Door_Detector
 * 
 * 
 * Deep Sleep for the HUZZAH.
 * ESP.deepSleep(uint32_microseconds)
 * So the max deep sleep is for ~71 mintues
 * https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep
 * https://blog.adafruit.com/2018/07/17/put-the-adafruit-huzzah-feather-esp8266-to-deep-sleep-with-one-wire-and-one-line-of-code/
 * 
 * **********************************************************************************************
 */

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// pin connected to DH22 data line
#define DATA_PIN 2

#define SLEEP_LENTH_MINUTES 5

// create DHT11 instance
DHT_Unified dht(DATA_PIN, DHT11);

// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *humidity = io.feed("humidity");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // initialize dht22
  dht.begin();

  //   ********** connect to io.adafruit.com    **********  
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());



  //  **********  Read the temperature/humidity sensor  **********
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  float celsius = event.temperature;
  float fahrenheit = (celsius * 1.8) + 32;

  Serial.print("celsius: ");
  Serial.print(celsius);
  Serial.println("C");

  Serial.print("fahrenheit: ");
  Serial.print(fahrenheit);
  Serial.println("F");

  // save fahrenheit (or celsius) to Adafruit IO
  temperature->save(fahrenheit);

  dht.humidity().getEvent(&event);

  Serial.print("humidity: ");
  Serial.print(event.relative_humidity);
  Serial.println("%");

  // save humidity to Adafruit IO
  humidity->save(event.relative_humidity);


  //    **********  Read the battery level    **********  
  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 1M & 220K voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 580 (3.14V)
  // and the max analog read value should be 774 (4.2V).
  int level = analogRead(A0);

  // convert battery level to percent
  level = map(level, 580, 774, 0, 100);
  Serial.print("Battery level: "); Serial.print(level); Serial.println("%");
  
  // grab the battery feed
  AdafruitIO_Feed *battery = io.feed("battery");
  
  // send battery level to AIO
  battery->save(level);





  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  //  Put the HUZZAH to sleep
  ESP.deepSleep(SLEEP_LENTH_MINUTES * 60 * 1000000);

}

void loop() {



  

  // wait 5 seconds (5000 milliseconds == 5 seconds)
  delay(60000);

}
