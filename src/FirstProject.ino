/*
 * Project FirstProject
 * Description: Blinking LED
 * Author: Kendra Tam
 * Date: December 23, 2019
 */

int led1 = D6;
//int led2 = D7;

int photosensor = A0; // This is where your photoresistor or phototransistor is plugged in. The other side goes to the "power" pin (below).
int analogvalue; // Here we are declaring the integer variable analogvalue, which we will use later to store the value of the photoresistor or phototransistor.

int ledToggle(String command); // Forward declaration
int ledToggle(String command); // Forward declaration

// setup() runs once, when the device is first turned on.
void setup() {
	// This is here to allow for debugging using the USB serial port
    Serial.begin();

	// Put initialization like pinMode and begin functions here.
	pinMode(led1, OUTPUT);
	//pinMode(led2, OUTPUT);

	digitalWrite(led1, HIGH);
	 // We are going to declare a Particle.variable() here so that we can access the value of the photosensor from the cloud.
    Particle.variable("analogvalue", &analogvalue, INT);
    // This is saying that when we ask the cloud for "analogvalue", this will reference the variable analogvalue in this app, which is an integer variable.

	// We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
	Particle.function("led",ledToggle);
	// This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

	// For good measure, let's also make sure both LEDs are off when we start:
	// digitalWrite(led1, LOW);
	// digitalWrite(led2, LOW);
	}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	/*
	// The core of your code will likely live here.
	// To blink the LED, first we'll turn it on...
	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);

	// We'll leave it on for 1 second...
	delay(1000);

	// Then we'll turn it off...
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);

	// Wait 1 second...
	delay(1000);

	// And repeat!
	*/

	// check to see what the value of the photoresistor or phototransistor is and store it in the int variable analogvalue
    analogvalue = analogRead(photosensor);

    // This prints the value to the USB debugging serial port (for optional debugging purposes)
    Serial.printlnf("%d", analogvalue);

    // This delay is just to prevent overflowing the serial buffer, plus we really don't need to read the sensor more than
    // 10 times per second (100 millisecond delay)
    delay(100);
}


// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.

int ledToggle(String command) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        digitalWrite(led1,HIGH);
        //digitalWrite(led2,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led1,LOW);
        //digitalWrite(led2,LOW);
        return 0;
    }
    else {
        return -1;
    }
}