/*
 * Project ParticleBoron
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */
#include "mavlink_data_types.h"

String phrase = "";
int dataType;
String fix = "";
String latitude = "";
String longitude = "";
String speed = "";
String satsVisible = "";

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

    Particle.variable("gpsFix", fix);
    Particle.variable("gpsLat", latitude);
    Particle.variable("gpsLong", longitude);
    Particle.variable("gpsSpeed", speed);
    Particle.variable("gpsSatsVis", satsVisible);
	}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    if (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        letter = incomingByte;
		Serial.print(letter);

        if (letter == ':' || count >= maxlimit) {
			dataType = phrase.toInt();
            phrase = "";
            count = 0;
        }
		else if (letter == '\n' || count >= maxlimit){
			switch(dataType) {
				case 0:
					fix = phrase;
					break;
				case 1:
					latitude = phrase;
					break;
				case 2:
					longitude = phrase;
					break;
				case 3:
					speed = phrase;
					break;
				case 4:
					satsVisible = phrase;
					break;
			}
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