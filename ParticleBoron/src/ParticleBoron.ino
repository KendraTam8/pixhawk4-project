/*
 * Project ParticleBoron
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */
#include "mavlink_data_types.h"

String orderReq = "";
bool isScanAuth = "";
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

String twilioMsg = "";
String twilioCMsg = "Connected1";
String twilioHMsg = "Connected2";
int stateSMS = 0;	// 0=nothing, 1=phone1standby|phone2askload, 2=2askauthtag 3=2asktakeoff, 4=depart+arrive, (5=error)
int infoSMS = 12;
String *mavlinkDataList[TOTAL_TYPES];
String mavlinkTypeList[TOTAL_TYPES];
int gotCount = 0;

String order = "";
int orderNum = 0;
int droneNum = 5;
int eta = 15;
int cardValid = 1;
bool isMsgSent = false;

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
	Particle.function("incomingSMS", incomingSMS);

	Particle.publish("twilio_clinic", twilioCMsg, PRIVATE);
	Particle.publish("twilio_hospital", twilioHMsg, PRIVATE);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	
	switch(stateSMS) {
		case 1:
			if (!isMsgSent) {
				Particle.publish("twilio_clinic", twilioCMsg, PRIVATE);
				Particle.publish("twilio_hospital", twilioHMsg, PRIVATE);
				isMsgSent = true;
			}
			break;
		case 2:
			if (cardValid) {
				Particle.publish("twilio_hospital", twilioHMsg, PRIVATE);
				//cardValid = 0;
				stateSMS = 3;
			}
			break;
		case 3:
			if (!isMsgSent) {
				twilioHMsg = "Scan accepted\nSend YES when clear for takeoff";	//get rid when arduino
				Particle.publish("twilio_hospital", twilioHMsg, PRIVATE);
				isMsgSent = true;
			}
			break;
		case 4:
			Particle.publish("twilio_hospital", twilioHMsg, PRIVATE);
			Particle.publish("twilio_clinic", twilioCMsg, PRIVATE);
			stateSMS = 0;
			isMsgSent = false;
			break;
		default:
			break;
	}

    if (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        letter = incomingByte;
		Serial.print(letter);
		if (stateSMS == 2) {
			cardValid = incomingByte;
			twilioHMsg = "Scan accepted\nSend YES when clear for takeoff";
		}
		else {
			if (letter == ':' || count >= MAX) {
				dataType = phrase.toInt();
				phrase = "";
				count = 0;
			}
			else if (letter == '\n' || count >= MAX){
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

int incomingSMS(String info) {
	switch(stateSMS) {
		case 0:
			//string seperating to determin order req
			orderReq = "5x Ebola Vaccines";
			isMsgSent = false;
			orderNum++;
			twilioCMsg = "Order #" + String(orderNum) + " Recieved:\n| " + orderReq + " |\nPlease standby";
			twilioHMsg = "Place Order #" + String(orderNum) + "\n| " + orderReq + " |\nIn drone: #"+ String(droneNum) + "\nSend YES when loaded";
			stateSMS = 1;
			break;
		case 1:
			if (info.toLowerCase() == "yes") {
				Serial1.println("!");
				twilioHMsg = "Scan authorization tag";
				stateSMS = 2;
				isMsgSent = false;
			}
			break;
		case 3:
			if (info.toLowerCase() == "yes") {
				isMsgSent = false;
				twilioHMsg = "Order #" + String(orderNum) + " Sent";
				twilioCMsg = "Your Order #" + String(orderNum) + "\n| " + orderReq + " |\nHas departed. ETA " + String(eta) + " mins";
				stateSMS = 4;
			}
			break;
	}
	return 1;
}
