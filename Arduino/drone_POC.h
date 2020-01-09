 /* 
  *  Pin Map  Arduino Nano
  *  
  *  RC522 RST D8
  *  RC522 SDA(SS) D10
  *  RC522 MOSI D11
  *  RC522 MISO D12
  *  RC522 SCK D13
  *  
  *  Indicator LED A4
  *  
  *  
  *  Mavlink RX 2
  *  Mavlink TX 3
  */



#include <mavlink.h>
#include <mavlink_data_types.h>
#include <MFRC522.h>

#include <SoftwareSerial.h>
#include <SPI.h>
#include "./authorizedCards.h"

//
// Mavlink Defines
//

#define NUM_HBS 60 // # of heartbeats to wait before activating STREAMS from Pixhawk. 60 = one minute.

#define SYS_ID 1 ///< ID 20 for this airplane. 1 PX, 255 ground station
#define COMP_ID 158 ///< The component sending the message
#define VEH_TYPE MAV_TYPE_QUADROTOR

// Define the system type, in this case an airplane -> on-board controller
#define SYS_TYPE MAV_TYPE_GENERIC
#define AUTOPILOT_TYPE MAV_AUTOPILOT_INVALID


//
// RFID Defines
//

#define SS_PIN 10
#define RST_PIN 9
#define BUZZ_PIN 7
#define BUTTON_PIN 5
#define LED_GREEN A2
#define LED_YELLOW A3
#define LED_RED A4

SoftwareSerial mySerial(2,3);   //RX, TX

uint32_t previousMillisMAVLink = 0;     // will store last time MAVLink was transmitted and listened
uint32_t next_interval_MAVLink = 1000;  // next interval to count

int num_hbs_pasados = NUM_HBS;

uint8_t system_mode = MAV_MODE_PREFLIGHT; ///< Booting up
uint32_t custom_mode = 0;                 ///< Custom mode, can be defined by user/adopter
uint8_t system_state = MAV_STATE_STANDBY; ///< System ready for flight

// Initialize the required buffers
mavlink_message_t msg;
uint8_t buf[MAVLINK_MAX_PACKET_LEN];

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

union cardData {
  uint32_t all;
  byte part[4]; 
} cardRead;
 
