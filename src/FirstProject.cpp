/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/kendr/OneDrive/Documents/GitHub/Particle/FirstProject/src/FirstProject.ino"
/*
 * Project FirstProject
 * Description: Blinking LED
 * Author: Kendra Tam
 * Date: December 23, 2019
 */

void setup();
void loop();
#line 8 "c:/Users/kendr/OneDrive/Documents/GitHub/Particle/FirstProject/src/FirstProject.ino"
int led1 = D7;

// setup() runs once, when the device is first turned on.
void setup() {
	// Put initialization like pinMode and begin functions here.
	pinMode(led1, OUTPUT);
	//pinMode(led2, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	// The core of your code will likely live here.
	// To blink the LED, first we'll turn it on...
	digitalWrite(led1, HIGH);
	//digitalWrite(led2, HIGH);

	// We'll leave it on for 1 second...
	delay(1000);

	// Then we'll turn it off...
	digitalWrite(led1, LOW);
	//digitalWrite(led2, LOW);

	// Wait 1 second...
	delay(1000);

	// And repeat!
}