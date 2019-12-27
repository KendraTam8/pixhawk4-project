/*
 * Project FirstProject
 * Description: 
 * Author: Kendra Tam
 * Date: December 23, 2019
 */

int led1 = D6;

String word = "";
String value = "";
int maxlimit = 64;
int count = 0;
int incomingByte;
char letter;

int ledToggle(String command); // Forward declaration

// setup() runs once, when the device is first turned on.
void setup() {
    // Set the keep-alive value for 3rd party SIM card here
    Particle.keepAlive(120);

    Serial.begin();
    Serial1.begin(9600);

	// Put initialization like pinMode and begin functions here.
	pinMode(led1, OUTPUT);
	digitalWrite(led1, HIGH);
	
    Particle.variable("returnValue", value);
	Particle.function("led",ledToggle);
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