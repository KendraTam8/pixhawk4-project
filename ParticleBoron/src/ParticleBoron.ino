/*
 * Project ParticleBoron
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */
#include "mavlink_data_types.h"

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
const int maxlimit = 1000;

String twilioMsg = "Type one of the coresponding numbers.\n";
bool incomingSMS = false;
int stateSMS = 0;	// 0=nothing, 1=first call, 2=get data, 3=done	
int infoSMS = 12;
String *mavlinkDataList[TOTAL_TYPES];

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
	for (int i=0; i<TOTAL_TYPES; i++) {
		twilioMsg += String(i) + " - ";
		switch(i) {
			case VOLT:
				ptr = &voltage;
				twilioMsg += "Voltage\n";
				break;
			case BATT_REMAIN:
				ptr = &battery;
				twilioMsg += "Battery\n";
				break;
			case GPS_LAT:
				ptr = &latitude;
				twilioMsg += "Latitude\n";
				break;
			case GPS_LONG:
				ptr = &longitude;
				twilioMsg += "Longitude\n";
				break;
			case GPS_SATS_VIS:
				ptr = &satsVisible;
				twilioMsg += "Satellites Visible\n";
				break;
			case ALT:
				ptr = &altitude;
				twilioMsg += "Altitude\n";
				break;
			case ALT_ROLL:
				ptr = &roll;
				twilioMsg += "Roll\n";
				break;
			case ALT_PITCH:
				ptr = &pitch;
				twilioMsg += "Pitch\n";
				break;
			case ALT_YAW:
				ptr = &yaw;
				twilioMsg += "Yaw\n";
				break;
			case MISS_CURR:
				ptr = &missionCurr;
				twilioMsg += "Mission Current Sequence\n";
				break;
			case VFR_AIRSPEED:
				ptr = &airspeed;
				twilioMsg += "Airspeed\n";
				break;
			case VFR_HEAD:
				ptr = &heading;
				twilioMsg += "Heading\n";
				break;
			default:
				ptr = NULL;
				break;
		}
		mavlinkDataList[i] = ptr;
	}
	ptr = NULL;
	delete ptr;
	twilioMsg += String(TOTAL_TYPES) + " - All of the Above";
	Particle.publish("twilio_sms", twilioMsg, PRIVATE);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	
	if (stateSMS == 1) {
		// total = 1;
		// if (infoSMS == 12) {
		// 	total = 12;
		// }
		stateSMS = 2;
		getMavlink("1");
	}
	else if (stateSMS == 3) {
		stateSMS = 0;
		Particle.publish("twilio_sms", twilioMsg, PRIVATE);
	}

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
				case VOLT:
					voltage = phrase;
					break;
				case BATT_REMAIN:
					battery = phrase;
					break;
				case GPS_LAT:
					latitude = phrase;
					break;
				case GPS_LONG:
					longitude = phrase;
					break;
				case GPS_SATS_VIS:
					satsVisible = phrase;
					break;
				case ALT:
					altitude = phrase;
					break;
				case ALT_ROLL:
					roll = phrase;
					break;
				case ALT_PITCH:
					pitch = phrase;
					break;
				case ALT_YAW:
					yaw = phrase;
					break;
				case MISS_CURR:
					missionCurr = phrase;
					break;
				case VFR_AIRSPEED:
					airspeed = phrase;
					break;
				case VFR_HEAD:
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
