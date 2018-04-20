#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// ================ | LIBRARIES
#include <Arduino.h>
#include <jm_Wire.h>      // i2c communications, arduino Wire problematic
#include <SPI.h>
#include <SD.h>

// ================ | SENSOR STUFF
#define SENSOR_PIN    0  // sensor pin
#define INTERRUPT_PIN 2  // interrupt associated to pin
#define DIGITS_SIZE   6  // how many digits in number

#define WARM_UP_TIME  45000
#define DEBOUNCE_TIME 7000
#define BROADCAST_TIME 3000

// ================ | COMMS
#define SLAVE_ADDRESS 1  // address of slave (single slave scenario)

#define SS_CHECK    0x21	// !
#define SS_WRBIN    0x00	// Write new value from bin
#define SS_WRVAL    0x01	// Write neww value from char
#define SS_WBRI     0x02	// Set Brightness
#define SS_RBOT     0x03  // Reboot
#define SS_MODE     0x04  // Change mode
#define SS_ACK      0x00  // Do acknowledge
#define SS_NO_ACK   0x01  // Do NOT acknowledge

// ================ | LOGGING
#define CHIPSELECT    4
#define FILENAME "datalog.csv"  // where data is saved
#define CSV_DELIM ","

// ================ | UTIL
#define intToByteArray(i) static_cast<char*>(static_cast<void*>(&i))
#define charDtoInt(c) (int)(c - 48) // will only be correct for decimals

#endif
