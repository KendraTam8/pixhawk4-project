#include "./drone_POC.h"

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

enum State {WAIT, SCAN, ACCEPT, REJECT};
enum State state;

void setup() { 
  mySerial.begin(9600);
  Serial.begin(57600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  digitalWrite(LED_RED, LOW);
  beepReady();

  state = SCAN;
}
 
void loop() { 
  
  // Pack the message
  mavlink_msg_heartbeat_pack(1, 0, &msg, VEH_TYPE, AUTOPILOT_TYPE, system_mode, custom_mode, system_state);
  
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the message with the standard UART send function
  // uart0_send might be named differently depending on
  // the individual microcontroller / library in use.
  unsigned long currentMillisMAVLink = millis();
  if (currentMillisMAVLink - previousMillisMAVLink >= next_interval_MAVLink) {
    // Timing variables
    previousMillisMAVLink = currentMillisMAVLink;

    Serial.write(buf, len);

    //Mav_Request_Data();
    num_hbs_pasados++;
    if(num_hbs_pasados>=NUM_HBS) {
    // Request streams from Pixhawk
    Mav_Request_Data();
    num_hbs_pasados=0;
    }
  }

  // Check reception buffer
  comm_receive();

  char infoRequest = mySerial.read();
  if (infoRequest == '*') {
    website_request();
  }
  else if (infoRequest == '!'){
    twilio_request();
  }

  if (true || state != ACCEPT) {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! rfid.PICC_IsNewCardPresent())
      return;
    
    // Verify if the NUID has been readed
    if ( ! rfid.PICC_ReadCardSerial())
      return;
    
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    
    // Check is the PICC of Classic MIFARE type
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      Serial.println(F("Incorrect Card Format, Should use MiFare classic, 1K or 4K"));
      return;
    }
    
    // Copy Card Data
    for (byte i = 0; i < 4; i++) {
      cardRead.part[i] = rfid.uid.uidByte[i];
    }
    
    Serial.println(cardRead.all, HEX);
    
    // Halt PICC
    rfid.PICC_HaltA();
    
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
    
    // Search Card
    for (int i = 0; i < sizeof(authorizedCards)/sizeof(authorizedCards[0]); i++) {
      if (cardRead.all == authorizedCards[i]) {
        // Card is in the authorized list, accept
        state = ACCEPT;
        digitalWrite(LED_RED, HIGH);
        beepAccept();
        return;
      }
    }
    // Did not find matching card, reject
    digitalWrite(LED_RED, LOW);
    beepReject();
    state = REJECT;
  }

}

void beepAccept() {
  tone(BUZZ_PIN,2093,250);
  delay(150);
  tone(BUZZ_PIN,2637,250);
  delay(150);
  tone(BUZZ_PIN,3135,500);
  delay(300);
}

void beepReject() {
  tone(BUZZ_PIN,3135,75);
  delay(100);
  tone(BUZZ_PIN,3135,75);
  delay(100);
  tone(BUZZ_PIN,3135,75);
  delay(100);
}

void beepReady(){
  tone(BUZZ_PIN,2637,250);
  delay(150);
  tone(BUZZ_PIN,2093,250);
  delay(150);
}

void beepScan(){
  tone(BUZZ_PIN,3135,100);
  delay(150);
}

void Mav_Request_Data()
{
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  
  // STREAMS that can be requested
  /*
  * Definitions are in common.h: enum MAV_DATA_STREAM
  *   
  * MAV_DATA_STREAM_ALL=0, // Enable all data streams
  * MAV_DATA_STREAM_RAW_SENSORS=1, /* Enable IMU_RAW, GPS_RAW, GPS_STATUS packets.
  * MAV_DATA_STREAM_EXTENDED_STATUS=2, /* Enable GPS_STATUS, CONTROL_STATUS, AUX_STATUS
  * MAV_DATA_STREAM_RC_CHANNELS=3, /* Enable RC_CHANNELS_SCALED, RC_CHANNELS_RAW, SERVO_OUTPUT_RAW
  * MAV_DATA_STREAM_RAW_CONTROLLER=4, /* Enable ATTITUDE_CONTROLLER_OUTPUT, POSITION_CONTROLLER_OUTPUT, NAV_CONTROLLER_OUTPUT.
  * MAV_DATA_STREAM_POSITION=6, /* Enable LOCAL_POSITION, GLOBAL_POSITION/GLOBAL_POSITION_INT messages.
  * MAV_DATA_STREAM_EXTRA1=10, /* Dependent on the autopilot
  * MAV_DATA_STREAM_EXTRA2=11, /* Dependent on the autopilot
  * MAV_DATA_STREAM_EXTRA3=12, /* Dependent on the autopilot
  * MAV_DATA_STREAM_ENUM_END=13,
  * 
  * Data in PixHawk available in:
  *  - Battery, amperage and voltage (SYS_STATUS) in MAV_DATA_STREAM_EXTENDED_STATUS
  *  - Gyro info (IMU_SCALED) in MAV_DATA_STREAM_EXTRA1
  */

  // To be setup according to the needed information to be requested from the Pixhawk
  // const int  maxStreams = 2;
  // const uint8_t MAVStreams[maxStreams] = {MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTRA1};
  // const uint16_t MAVRates[maxStreams] = {0x02,0x05};
  uint8_t _system_id = 20; // id of computer which is sending the command (ground control software has id of 255)
  uint8_t _component_id = 158; // seems like it can be any # except the number of what Pixhawk sys_id is
  uint8_t _target_system = 1; // Id # of Pixhawk (should be 1)
  uint8_t _target_component = MAV_COMP_ID_ALL; // Target component, 0 = all (seems to work with 0 or 1
  uint8_t _req_stream_id = MAV_DATA_STREAM_ALL;
  uint16_t _req_message_rate = 0x01; //number of times per second to request the data in hex
  uint8_t _start_stop = 1; //1 = start, 0 = stop  
  /*
  for (int i=0; i < maxStreams; i++) {
    /*
    * mavlink_msg_request_data_stream_pack(system_id, component_id, 
    *    &msg, 
    *    target_system, target_component, 
    *    MAV_DATA_STREAM_POSITION, 10000000, 1);
    *    
    * mavlink_msg_request_data_stream_pack(uint8_t system_id, uint8_t component_id, 
    *    mavlink_message_t* msg,
    *    uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, 
    *    uint16_t req_message_rate, uint8_t start_stop)
    * 
    *
    mavlink_msg_request_data_stream_pack(2, 200, &msg, 1, 0, MAV_DATA_STREAM_ALL, 0x02, 1);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    Serial.write(buf, len);
  }
  */
  mavlink_msg_request_data_stream_pack(2, 200, &msg, _target_system, _target_component, _req_stream_id, _req_message_rate, _start_stop);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}

void comm_receive() {
  mavlink_message_t msg;
  mavlink_status_t status;

  while(Serial.available()>0) {
    uint8_t c = Serial.read();
    //mySerial.println(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status));
    
    // Try to get a new message
    if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
    // Handle message
    switch(msg.msgid) {
    case MAVLINK_MSG_ID_SYS_STATUS:  // #1
    {
    mavlink_sys_status_t sys_status;
    mavlink_msg_sys_status_decode(&msg, &sys_status);

    voltage = sys_status.voltage_battery;
    battery = sys_status.battery_remaining;
    }
    break;
    
    case MAVLINK_MSG_ID_GPS_RAW_INT:  //#24
    {
    mavlink_gps_raw_int_t gps_raw;
    mavlink_msg_gps_raw_int_decode(&msg, &gps_raw);
    

    latitude = gps_raw.lat;
    longitude = gps_raw.lon;
    satsVisible = gps_raw.satellites_visible;
    altitude = gps_raw.alt;
    }
    break;
    
  case MAVLINK_MSG_ID_ATTITUDE:  // #30
  {
  mavlink_attitude_t attitude;
  mavlink_msg_attitude_decode(&msg, &attitude);
    
  roll = attitude.roll;
  pitch = attitude.pitch;
  yaw = attitude.yaw;
  }
  break;

  case MAVLINK_MSG_ID_MISSION_CURRENT:  // #42
  {
    mavlink_mission_current_t mission_current;
    mavlink_msg_mission_current_decode(&msg, &mission_current);
    
    missionCurr = mission_current.seq;
  }
  break;

  case MAVLINK_MSG_ID_VFR_HUD:  // #74
  {
    mavlink_vfr_hud_t vfr_hud;
    mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
    
    airspeed = vfr_hud.airspeed;
    heading = vfr_hud.heading;
  }
  break;

    default:
    break;
  }
  }
  }
}

void website_request() {
  //sys
  mySerial.print(VOLT);mySerial.print(":0|");mySerial.println(voltage);
  mySerial.print(BATT_REMAIN);mySerial.print(":1|");mySerial.println(battery);

  //gps
  mySerial.print(GPS_LAT);mySerial.print(":");mySerial.println(latitude);
  mySerial.print(GPS_LONG);mySerial.print(":");mySerial.println(longitude);
  mySerial.print(GPS_SATS_VIS);mySerial.print(":4|");mySerial.println(satsVisible);
  mySerial.print(ALT);mySerial.print(":5|");mySerial.println(altitude);

  //attitude
  mySerial.print(ALT_ROLL);mySerial.print(":6|");mySerial.println(roll);
  mySerial.print(ALT_PITCH);mySerial.print(":7|");mySerial.println(pitch);
  mySerial.print(ALT_YAW);mySerial.print(":8|");mySerial.println(yaw);

  //mission current
  mySerial.print(MISS_CURR);mySerial.print(":9|");mySerial.println(missionCurr);

  //vfr
  mySerial.print(VFR_AIRSPEED);mySerial.print(":10|");mySerial.println(airspeed);
  mySerial.print(VFR_HEAD);mySerial.print(":11|");mySerial.println(heading);
}

void twilio_request() {
  mySerial.print("1");
}
