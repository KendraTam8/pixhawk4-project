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

String phrase = "";
int dataType;
int count = 0;
int incomingByte;
char letter;
const int MAX = 500;

String twilioMsg = "Type one of the coresponding numbers.\n";
int stateSMS = 1;	// 0=nothing, 1=first call, 2=get data, 3=done	
int infoSMS = 12;
String *mavlinkDataList[TOTAL_TYPES];
String mavlinkTypeList[TOTAL_TYPES];
int gotCount = 0;

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

    Particle.variable("infoSMS", infoSMS);
    Particle.variable("stateSMS", stateSMS);

	Particle.function("getMavlink", getMavlink);

	String *ptr;
	String name;
	for (int i=0; i<TOTAL_TYPES; i++) {
		twilioMsg += String(i) + " - ";
		switch(i) {
			case VOLT:
				ptr = &voltage;
				name = "Voltage";
				break;
			case BATT_REMAIN:
				ptr = &battery;
				name = "Battery";
				break;
			case GPS_LAT:
				ptr = &latitude;
				name = "Latitude";
				break;
			case GPS_LONG:
				ptr = &longitude;
				name = "Longitude";
				break;
			case GPS_SATS_VIS:
				ptr = &satsVisible;
				name = "Satellites Visible";
				break;
			case ALT:
				ptr = &altitude;
				name = "Altitude";
				break;
			case ALT_ROLL:
				ptr = &roll;
				name = "Roll";
				break;
			case ALT_PITCH:
				ptr = &pitch;
				name = "Pitch";
				break;
			case ALT_YAW:
				ptr = &yaw;
				name = "Yaw";
				break;
			case MISS_CURR:
				ptr = &missionCurr;
				name = "Mission Current Sequence";
				break;
			case VFR_AIRSPEED:
				ptr = &airspeed;
				name = "Airspeed";
				break;
			case VFR_HEAD:
				ptr = &heading;
				name = "Heading";
				break;
			default:
				ptr = NULL;
				name = "";
				break;
		}
		twilioMsg += name + "\n";
		mavlinkDataList[i] = ptr;
		mavlinkTypeList[i] = name;
	}
	ptr = NULL;
	delete ptr;
	twilioMsg += String(TOTAL_TYPES) + " - All of the Above";
	Particle.publish("twilio_sms", twilioMsg, PRIVATE);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	
	if (stateSMS == 1) {
		if (infoSMS > TOTAL_TYPES || infoSMS < 0) {
			stateSMS = 0;
			Particle.publish("twilio_sms", "Invalid Input.", PRIVATE);
		} 
		else {
			gotCount = 0;
			stateSMS = 2;
			getMavlink("1");
		}
	}
	else if (stateSMS == 3) {
		twilioMsg = "REQUESTED DATA\n";
		if (infoSMS == 12 ) {
			for (int i=0; i<TOTAL_TYPES; i++) {
				twilioMsg += mavlinkTypeList[i] + ": " + *mavlinkDataList[i] + "\n";
			}
		}
		else {
			twilioMsg += mavlinkTypeList[infoSMS] + ": " + *mavlinkDataList[infoSMS];
		}

		stateSMS = 0;
		Particle.publish("twilio_sms", twilioMsg, PRIVATE);
	}

    if (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        letter = incomingByte;
		Serial.print(letter);
        if (letter == ':' || count >= MAX) {

			dataType = phrase.toInt();
            phrase = "";
            count = 0;
        }
		else if (letter == '\n' || count >= MAX){
			switch(dataType) {
				case VOLT:
					voltage = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case BATT_REMAIN:
					battery = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case GPS_LAT:
					latitude = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case GPS_LONG:
					longitude = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case GPS_SATS_VIS:
					satsVisible = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case ALT:
					altitude = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case ALT_ROLL:
					roll = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case ALT_PITCH:
					pitch = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case ALT_YAW:
					yaw = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case MISS_CURR:
					missionCurr = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case VFR_AIRSPEED:
					airspeed = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				case VFR_HEAD:
					heading = phrase;
					if (stateSMS == 2) {
						gotCount++;
					}
					break;
				default:
					break;
			}
			if (stateSMS == 2 && gotCount >= TOTAL_TYPES) {
				stateSMS = 3;
				gotCount = 0;
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
