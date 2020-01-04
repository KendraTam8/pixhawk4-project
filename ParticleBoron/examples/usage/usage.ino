// Example usage for mavlink_data_types library by Kendra Tam.

#include "mavlink_data_types.h"

// Initialize objects from the lib
Mavlink_data_types mavlink_data_types;

void setup() {
    // Call functions on initialized library objects that require hardware
    mavlink_data_types.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    mavlink_data_types.process();
}
