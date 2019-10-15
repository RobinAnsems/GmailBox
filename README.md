# GmailBox
In this manual I will show you how I created the code for the 'GmailBox'. GmailBox is a project for school I did with Andrei. GmailBox is a typical American Mailbox which we made smart. With GmailBox you can mark your Email as 'read'. This is an image which demonstrates the looks and interactions when you get an Email:

![1](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/1.png)

With Zapier we are going to connect your Gmail with Adafruit IO. When you get an Email, Zapier will send data to Adafruit IO. Your Arduino will pull data from Adafruit IO so you can simulate an Email coming in.

We will make the following things in Arduino:
* The flag that GmailBox will pull up when you get an Email. We will do this with a servomotor. 
* The notification-sound. We will do this with a piezo buzzer. 
* Ledstrip from the GmailBox. We will do this with a NeoPixel.
* To mark your Email as 'read', we will use a HRC-SR04 Ultrasound distance-sensor.

## Prerequisites
### Hardware
For the GmailBox-code we are going to use the following hardware:
* An ESP8266
* An Adafruit NeoPixel
* An Ultrasonic Sensor HC-SR04
* A Piezo Buzzer
* A SG90 Mini Analog servomotor

### Libaries
For the GmailBox-code we are going to use the following libaries:
* A config file
* ESP8266WiFi Library
* ESP8266HTTPClient Library
* Adafruit NeoPixel Library
* Servo Library

(I will show you how to use these libraries in our Adruino-code)

### Accounts
Register for a Zapier account
* [Zapier](https://zapier.com/sign-up/)

Register for a Adafruit IO account
* [Adafruit IO](https://accounts.adafruit.com/users/sign_up)


## Manual
### Setup Zapier to connect Gmail with Adafruit IO
When you are logged in on Zapier, click on the button called "Make a Zap!" as shown below:

![2](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/2.png)

The first step is to name your zap on the topleft, I called my zap "GmailBox". When you have done this, choose Gmail as the "App & Event" as shown below:

![3](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/3.png)

For your "Trigger Event", scroll down in the dropdownmenu en choose choose "New Email". Click on Continue.

The next step is to choose your Gmail-account as shown below. When you have done that, click on Continue.

![4](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/4.png)

At "Customize Email" choose the inbox that you want, this can also be a labeled-inbox, I chose for "INBOX" so I get a notification in GmailBox everytime I get an Email, as shown below. Click on Continue.

![5](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/5.png)

At "Find Data" click the button called "Test & Review" It will show you test-emails, choose "Email A" as shown below. Click on "Done Editing".

![6](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/6.png)

The Next step is to connect our Gmail-signal with Adafruit IO. First we need to do some things in Adafruit IO, then we will come back to Zapier.

When you are logged in on Adafruit IO, click on the tab called "Feeds" at the top, as shown below:
 
![7](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/7.png)

When you are there, you click on the dropdownbutton called "Actions" and click on "Create a New Feed" as shown below:

![8](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/8.png)

In the popup-menu fill under "Name" this in: "gmailbox", lowercase, as shown below. This will be your feed-key! Click on "Create".

![9](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/9.png)

Thats it for Adafruit IO.

We will move back to Zapier to complete the steps.

Click on "2. Do This ..." and in the searchbar, search for Adafruit IO as shown below.

![10](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/10.png)

For "Choose Action Event" click the dropdownmenu and choose "Create Feed Data" and click on Continue.

Choose your Adafruit IO account as shown below and click on Continue.

![11](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/11.png)

At "Customize Feed Data" for "Feed Key" click on the dropdownmenu and choose "Custom Value" as shown below.

![12](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/12.png)

For "Custom Value for Feed Key" fill in your feed-key you created at Adafruit IO a few steps back. For "Value" fill in: "1". It should look shomething like this:

![13](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/13.png)

Click on Continue. Press the button called "Test & Continue"

You just created your first Zap! Congrats! Turn on your Zap as shown below:

![14](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/14.png)

Now we are going to code the GmailBox in Arduino.
***

### Write code for GmailBox in Arduino
First you need to create a new Arduino file. When you have done that you need create a config file in the same folder as your Arduino file. You should have something like this (a config file inside the projectfolder, next to the Arduino-file you are going to work on):

![15](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/15.png)

Now we need to link these two files together, in your Arduino-file, above the setup, paste this code:

```
#include "config.h"                                 // include the config file where your Adafruit username, key and your WIFI settings will be at

#include <ESP8266WiFi.h>                            // include the ESP8266 WIFI library
#include <ESP8266HTTPClient.h>                      // include the ESP8266 HTTP Client library                    
```

Remove every code that is in your config-file and paste the following code:

```
/************************ Adafruit IO Config *******************************/

#define IO_USERNAME  "YOUR ADAFRUIT IO USERNAME HERE"
#define IO_KEY       "YOUR ADAFRUIT IO KEY HERE"

/******************************* WIFI **************************************/

#define WIFI_SSID   "YOUR WIFI NAME HERE"
#define WIFI_PASS   "YOUR WIFI PASSWORD HERE"

#include "AdafruitIO_WiFi.h"
```

You have to fill in your WIFI name and password to connect to the internet.
You also have to fill in your username and key, which can be found when you click the yellow "AIO Key"-button in Adafruit IO as shown below:

![16](https://github.com/RobinAnsems/GmailBox/blob/master/readme-images/16.png)


#### Connect Arduino with Adafruit IO

The next step is to connect your Arduino with Adafruit IO. Above the setup you have to paste this code to setup the feedkey for Adafruit IO:

```
AdafruitIO_Feed *gmailbox = io.feed("gmailbox");    // setup the feedkey for Adafruit IO                  
```

Now we get to the "void setup". Paste this code in the setup:

```
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

  gmailbox->onMessage(handleMessage);               // if an Email comes in 'handeMessage' will be run
}
```

Now we get to the "void loop". Paste this code in de loop:

```
void loop() {
  io.run();                                         // search Adafruit IO for signals of an Email
}
```

Now if you upload your code, you should see if your Arduino can connect to Adafruit IO. You can see this in the Serial Monitor.

If you have succesfully connected with Adafruit IO we can write code for when we get an Email, we will do this with a servomotor to simulate the flag going up on the GmailBox.

#### Flag from GmailBox simulated with a servomotor

For the servomotor we need to add a library above the setup. Paste this code above your setup:

```
#include <Servo.h>                                  // include the Servo library
Servo myServo;                                      // make a servoObject with the name 'myServo'
```

To define the servo we have to put some code in the setup, I put the servo in D6 on my ESP8266. In your setup paste this code:

```
  myServo.attach(D6);                               // define the pin for the servomotor
  myServo.write(0);                                 // set the servomotor to zero degrees
```

We are going to make a new 'void' named: "void handleMessage". It should look something like this below. If we get an Email, the servo is going to be 90 degrees (flag up). If the value (Adafruit IO value) is bigger than 1 (1 Email), the flag will go up!

```
void handleMessage(AdafruitIO_Data *data) {         // if an Email comes in 'handeMessage' will be run
if (data > 0){                                       // if the value is bigger than zero in Adafruit IO
  myServo.write(90);                                // set the servomotor to 90 degrees 
  delay(1000);                                      // a second between actions because the servomotor is not that fast
  Serial.println("flag up");                        // serial print "flag up"
 }
  else {                                            // else the value is still 0 in Adafruit IO 
    myServo.write(0);                               // set the servomotor to zero degrees 
    delay(1000);                                    // a second delay
    Serial.println("no mail");                      // serial print "no mail"
  }
} 
```

Now if you upload your code and you send yourself an Email, your servomotor should rotate 90 degrees.

#### Mark the Email as 'read' with a gesture

We are going to use the distance-sensor for the gesture. When you are closer than 10 centimeters with your hand away from the sensor (GmailBox) our flag has to go down, because we 'read' the Email. Let's get started.

For the distance-sensor you need to define the trigger- and echopin above the setup:

```
#define trigPin D1                                  // define the trigger pin for the distance-sensor
#define echoPin D2                                  // define the echo pin for the distance-sensor
```

To define the distance-sensor we have to put some code in the setup. In your setup paste this code:

```
  pinMode(trigPin, OUTPUT);                         // define the trigger pin as output
  pinMode(echoPin, INPUT);                          // define the echo pin as input
```

In your loop you need to paste the following distance-sensor-code to get the sensor working:

```
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
```

If the distance is smaller than 10 centimeters the servo has to be 0 degrees (flag down). In your loop paste the following code:

```
if (distance <= 10) {                               // if the distance to the motionsensor is smaller then 10 centimeters
  myServo.write(0);                                 // set the servomotor to zero degrees 
  }
```

You can now mark the Email as 'read' with a gesture (your hand in front of the distance-sensor), the servomotor will go to zero degrees (flag down) if your hand is in 10 centimeters from the sensor.

#### Add a ledstrip (NeoPixel)

The Adafruit IO NeoPixel uses a library. I put the pin from the NeoPixel in D3 and I have a NeoPixel with 30 leds, change these values to your NeoPixel if needed. Above the setup you need to paste this code to get the NeoPixel working:

```
#include <Adafruit_NeoPixel.h>                      // include the Adafruit NeoPixel library
#define PIXEL_PIN     D3                            // define the pin for your NeoPixel
#define PIXEL_COUNT   30                            // define the number of leds in your NeoPixel
#define PIXEL_TYPE    NEO_GRB + NEO_KHZ800          // define the type of your NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);     // make a variable with the name 'pixels' 
```
 
In the setup we are going to paste code which turns on the NeoPixel:

```
  pixels.begin();                                   // start your NeoPixel
  pixels.show();                                    // shows your NeoPixel
```

If we put our hand before the distance-sensor, we want the NeoPixel to turn off, we do this bij putting the code below, under the if statement in the loop which sets the servo to zero degrees when the distance is smaller then 10 centimeters. 

```
  for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel
    pixels.setPixelColor(i, 0, 0, 0);               // pixelcolor set to zero, lights off
    pixels.show();                                  // shows your NeoPixel
    }
```

It should look something like this:

```
if (distance <= 10) {                               // if the distance to the motionsensor is smaller then 10 centimeters
  myServo.write(0);                                 // set the servomotor to zero degrees 
   
  for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel
    pixels.setPixelColor(i, 0, 0, 0);               // pixelcolor set to zero, lights off
    pixels.show();                                  // shows your NeoPixel
    }
  }
```

But when there is an Email, we want the NeoPixel to turn on, we do this bij putting the code below, under the if statement in the 'void handleMessage'.

```
for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel 
    pixels.setPixelColor(i, 213, 70, 56);           // pixelcolor set to the Gmail-color
    pixels.show();                                  // shows your NeoPixel
    }
```

It should look something like this:

```
 if (data > 0){                                     // if the value is bigger than zero in Adafruit IO
  myServo.write(90);                                // set the servomotor to 90 degrees 
  delay(1000);                                      // a second between actions because the servomotor is not that fast
  Serial.println("flag up");                        // serial print "flag up"

  for( int i = 0; i<PIXEL_COUNT; i++){              // for loop that turns off every led in the NeoPixel 
    pixels.setPixelColor(i, 213, 70, 56);           // pixelcolor set to the Gmail-color
    pixels.show();                                  // shows your NeoPixel
    }
 }
```

Now if you get an Email, your NeoPixel should light up, and when you put you hand in front of the distance-sensor, the NeoPixel should turn off.

#### Add a notification-sound (Piezo Buzzer)

To add a sound when we get an Email, we have to put the code below under the if statement in the 'void handleMessage'. I put my pin in D8.

```
  tone(D8, 200, 200);                               // notification-sound in the format (pin, toneheight, tonelength)
  delay(500);                                       // half a second between tones
  tone(D8, 300, 500);                               // notification-sound in the format (pin, toneheight, tonelength)
  delay(1000);                                      // a second delay
```

It should look something like this:

```
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
```
Thats it! You have created the code for 'GmailBox'.

To review the full code, clone the repository or download the zip-file.

## Author
* **Robin Ansems** - [Robin Ansems](https://github.com/RobinAnsems)
