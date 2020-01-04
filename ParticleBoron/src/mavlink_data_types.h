#pragma once

/* mavlink_data_types library by Kendra Tam
 */

// // This is your main class that users will import into their application
// class Mavlink_data_types
// {
// public:
//   /**
//    * Constructor
//    */
//   Mavlink_data_types();

//   /**
//    * Example method
//    */
//   void begin();

//   /**
//    * Example method
//    */
//   void process();

// private:
//   /**
//    * Example private method
//    */
//   void doit();
// };

typedef enum {
	GPS_FIX,
	GPS_LAT,
	GPS_LONG,
	GPS_SPEED,
	GPS_SATS_VIS
} mavlink_info;