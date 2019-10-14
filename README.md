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
For the GmailBox-code e are going to use the following libaries:
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




















First we need to create a cluster. On mongoDB you can have 1 cluster for free.
Create your first cluster.
![Setup 0](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/MongoDB-Setup-0.png)

Select your data plan. (I will choose for the free one)
![Setup 1](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/MongoDB-Setup-1.png)

Select the country where your database will be hosted and choose a name for your database.
![Setup 2](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/MongoDB-Setup-2.png)

Wait a few minutes to let them create your 'Cluster'.
![Setup 3](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/MongoDB-Setup-3.png)

Congratulations! You have created your first database using MongoDB
***

### Create your nodeJS project
If you dont have NodeJS installed on your computer make sure to follow the following steps on:
[NodeJS - Setup](https://www.webucator.com/how-to/how-install-nodejs-on-mac.cfm)

#### Initial 
Open the terminal and navigate to your project map. Run the following code to create a nodeJS project
```
Npm run init
```
This will give you a few questions to setup your project. Try to answer them and press enter to finish the setup

Create a file named 'server.js' and edit the 'main' in package.json to server.js
```json
"main": "server.js",
```

Before we can go further we need to install some libaries. We can do this by typing 'npm install libarieName'.
We are going to use the following:
```
npm install express --save
npm install mongodb --save
npm install mongoose --save
npm install body-parser --save
```

#### Form to database
First we are going to create a webpage where we can edit the values in the database.
Create a file named index.html with the following code.
```html
<!DOCTYPE html>
<html>
<head>
    <title>Form to MongoDB</title>
</head>

<body>
<h1>Form to MongoDB</h1>
<form method="post" action="/addname">
    <label>Enter Your Name</label><br>
    <input type="text" name="firstName" placeholder="Enter first name..." required >
    <input type="text" name="lastName" placeholder="Enter last name..." required >
    <input type="submit" value="Add Name">
</form>
</body>
</html>
```

In server js we are going to set the path to this file with express using the following code.
```javascript
const express = require("express");
const app = express();
const port = 3000;

app.use("/", (req, res) => {
    res.sendFile(__dirname + "/index.html");
});

app.listen(port, () => {
    console.log("Server listening on port " + port);
});
```
You can test if this is working by going to the terminal and typing in:
```
node server.js
```
This will run the server and show it on localhost:3000

Next up we will setup the files to send it to the database.

Follow the first steps.
![Setup 1](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/mongodb-step-1.png)

For this we will need to connection url which you can find under the connect button.
![Setup 1](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/connect-url-0.png)
Then copy the link and add your credentials under username and password
![Setup 1](https://github.com/smuldesign/BikeBoxApi/blob/master/readme-images/connect-url-1.png)

Now we need to add to following code below: Port = 3000;
This will create the schema which mongodb will use to create the database.
Add the username and password of the database user you created in step 1 form the mongodb setup.
```javascript
const mongoose = require("mongoose");
mongoose.Promise = global.Promise;
mongoose.connect("mongodb+srv://<user>:<password>@bikeboxapi-l7jii.mongodb.net/test?retryWrites=true&w=majority");

var nameSchema = new mongoose.Schema({
    firstName: String,
    lastName: String
});

var User = mongoose.model("User", nameSchema);
```

Next up we are gonna add the body parser to read the form.
You can do this by adding the following code;
```javascript
const bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
```

We are almost done with adding the form to the database. We now need to listen to a post command on the server. This piece of code will make sure your data gets proccessed and saved to the database.
```javascript
app.post("/addname", (req, res) => {
    let myData = new User(req.body);
    myData.save()
        .then(item => {
            res.send("item saved to database");
        })
        .catch(err => {
            res.status(400).send("unable to save to database");
        });
});
```

Now you can test the form.
start the server and submit a name.
If everything is done well you can see the name on mongodb.com under collections button.

#### How do we get this data to a json?
For this I will use the latest post of the User database. 
```javascript
app.get("/url", (req, res, next) => {
    User.find({}, {}, { sort: { date: -1 } }, function(err, post) {
        res.json(post[post.length - 1]);
    });
});
```
To test if the latest submit is being show go to the url; localhost:3000/url
We got a working form to json server. Whenever you want to change the way this form looks you have to make to edit the :
```javascript
var nameSchema = new mongoose.Schema({
    firstName: String,
    lastName: String
});
```
as well.

For the full code clone the repository

## Author
* **Rico Zethof** - [Rico Zethof](https://github.com/rico1136)
