#include "config.h"                                 // include the config file where your Adafruit username, key and your WIFI settings will be at

#include <ESP8266WiFi.h>                            // include the ESP8266 WIFI library
#include <ESP8266HTTPClient.h>                      // include the ESP8266 HTTP Client library

#define trigPin D1                                  // define the trigger pin for the distance-sensor
#define echoPin D2                                  // define the echo pin for the distance-sensor

#include <Servo.h>                                  // include the Servo library
Servo myServo;                                      // make a servoObject with the name 'myServo'

#include <Adafruit_NeoPixel.h>                      // include the Adafruit NeoPixel library
#define PIXEL_PIN     D3                            // define the pin for your NeoPixel
#define PIXEL_COUNT   30                            // define the number of leds in your NeoPixel
#define PIXEL_TYPE    NEO_GRB + NEO_KHZ800          // define the type of your NeoPixel

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);     // make a variable with the name 'pixels' 

AdafruitIO_Feed *gmailbox = io.feed("gmailbox");    // setup the feedkey for Adafruit IO

void setup() {
  Serial.begin(115200);                             // start the serial connection

  while(! Serial);                                  // wait for serial monitor to open

  Serial.print("Connecting to Adafruit IO");        // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the 'gmailbox' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.

  while(io.status() < AIO_CONNECTED) {              // wait for a connection
    Serial.print(".");                              // serial print dots
    delay(500);                                     // half a second between serial print
  }

  // message for when we are connected to Adafruit IO
  Serial.println();                                
  Serial.println(io.statusText());
  gmailbox->get();
    
  pixels.begin();                                   // start your NeoPixel
  pixels.show();                                    // shows your NeoPixel

  pinMode(trigPin, OUTPUT);                         // define the trigger pin as output
  pinMode(echoPin, INPUT);                          // define the echo pin as input

  myServo.attach(D6);                               // define the pin for the servomotor
  myServo.write(0);                                 // set the servomotor to zero degrees

  gmailbox->onMessage(handleMessage);               // if an Email comes in 'handeMessage' will be run
}

void loop() {
  io.run();                                         // search Adafruit IO for signals of an Email
      
  long duration, distance;                          // make a variable for duration and distance
  digitalWrite(trigPin, LOW);                       // give no pulse to the motionsensor 
  delayMicroseconds(2);                             // time between pulses
  digitalWrite(trigPin, HIGH);                      // give a pulse to the motionsensor
  delayMicroseconds(10);                            // time between pulses
  digitalWrite(trigPin, LOW);                       // give no pulse to the motionsensor
  duration = pulseIn(echoPin, HIGH);                // setup the duration
  distance = (duration/2) / 29.1;                   // setup the distance
  Serial.print(distance);                           // serial print the distance in the serial monitor
  Serial.println(" cm");                            // serial print the distance in centimeters
  delay(500);                                       // half a second between serial print

if (distance <= 10) {                               // if the distance to the motionsensor is smaller then 10 centimeters
  myServo.write(0);                                 // set the servomotor to zero degrees 
   
  for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel
    pixels.setPixelColor(i, 0, 0, 0);               // pixelcolor set to zero, lights off
    pixels.show();                                  // shows your NeoPixel
    }
  }
}

void handleMessage(AdafruitIO_Data *data) {         // if an Email comes in 'handeMessage' will be run
 if (data > 0){                                     // if the value is bigger than zero in Adafruit IO
  myServo.write(90);                                // set the servomotor to 90 degrees 
  delay(1000);                                      // a second between actions because the servomotor is not that fast
  Serial.println("flag up");                        // serial print "flag up"

  for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel 
    pixels.setPixelColor(i, 213, 70, 56);           // pixelcolor set to the Gmail-color
    pixels.show();                                  // shows your NeoPixel
    }

  tone(D8, 200, 200);                               // notification-sound in the format (pin, toneheight, tonelength)
  delay(500);                                       // half a second between tones
  tone(D8, 300, 500);                               // notification-sound in the format (pin, toneheight, tonelength)
  delay(1000);                                      // a second delay

 }
  else {                                            // else the value is still 0 in Adafruit IO 
    myServo.write(0);                               // set the servomotor to zero degrees 
    delay(1000);                                    // a second delay
    Serial.println("no mail");                      // serial print "no mail"
  }
}
