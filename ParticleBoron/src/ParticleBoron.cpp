/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/kendr/OneDrive/Documents/GitHub/Particle/ParticleBoron/src/ParticleBoron.ino"
/*
 * Project ParticleBoron
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */

void setup();
void loop();
#line 8 "c:/Users/kendr/OneDrive/Documents/GitHub/Particle/ParticleBoron/src/ParticleBoron.ino"
String phrase = "";
String value = "";
int maxlimit = 1000;
int count = 0;
int incomingByte;
char letter;

// setup() runs once, when the device is first turned on.
void setup() {
    // Set the keep-alive value for 3rd party SIM card here
    Particle.keepAlive(120);

    Serial.begin();
    Serial1.begin(9600);

	
    Particle.variable("returnValue", value);
	}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    if (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        letter = incomingByte;
        if (letter == '*' || count >= maxlimit) {
            value = phrase;
            Serial.println(value);
            phrase = "";
            count = 0;
        }
        else {
            count++;
            phrase += letter;
        }
    }
	delay(10);
}