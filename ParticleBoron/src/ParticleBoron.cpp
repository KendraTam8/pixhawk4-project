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
#include "mavlink_data_types.h"

void setup();
void loop();
int getMavlink(String request);
#line 9 "c:/Users/kendr/OneDrive/Documents/GitHub/Particle/ParticleBoron/src/ParticleBoron.ino"
String phrase = "";
int dataType;

String voltage = "";
String battery = "";
String latitude = "";
String longitude = "";
String satsVisible = "";
String altitude = "";
String roll = "";
String pitch = "";
String yaw = "";
String missionCurr = "";
String airspeed = "";
String heading = "";
bool requestData = false;

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

    Particle.variable("voltage", voltage);
    Particle.variable("battery", battery);
    Particle.variable("gpsLat", latitude);
    Particle.variable("gpsLong", longitude);
    Particle.variable("gpsSatsVis", satsVisible);
    Particle.variable("altitude", altitude);
    Particle.variable("roll", roll);
    Particle.variable("pitch", pitch);
    Particle.variable("yaw", yaw);
    Particle.variable("missionCurrent", missionCurr);
    Particle.variable("airspeed", airspeed);
    Particle.variable("heading", heading);

	Particle.function("getMavlink", getMavlink);
	}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    if (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        letter = incomingByte;
		//phrase += letter;
		Serial.print(letter);
        if (letter == ':' || count >= maxlimit) {
			//Serial.print(phrase);

			dataType = phrase.toInt();
            phrase = "";
            count = 0;
        }
		else if (letter == '\n' || count >= maxlimit){
			//Serial.print(phrase);
			switch(dataType) {
				case 0:
					voltage = phrase;
					break;
				case 1:
					battery = phrase;
					break;
				case 2:
					latitude = phrase;
					break;
				case 3:
					longitude = phrase;
					break;
				case 4:
					satsVisible = phrase;
					break;
				case 5:
					altitude = phrase;
					break;
				case 6:
					roll = phrase;
					break;
				case 7:
					pitch = phrase;
					break;
				case 8:
					yaw = phrase;
					break;
				case 9:
					missionCurr = phrase;
					break;
				case 10:
					airspeed = phrase;
					break;
				case 11:
					heading = phrase;
					break;
				default:
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
	delay(5);
}

int getMavlink(String request) {
	if (request == "1") {
		Serial1.println("*");
		return 1;
	}
	return 0;
}