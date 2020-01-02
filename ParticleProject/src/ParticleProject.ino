/*
 * Project ParticleProject
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */

String word = "";
String value = "";
int maxlimit = 64;
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
        if (letter == '\n' || count >= maxlimit) {
            value = word;
            Serial.println(value);
            word = "";
            count = 0;
        }
        else {
            count++;
            word += letter;
        }

    }
	delay(10);
}\