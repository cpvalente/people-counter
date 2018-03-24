#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <Wire.h>       // i2c communications
#include <SPI.h>
#include <SD.h>

#define SENSOR_PIN    0  // sensor pin
#define INTERRUPT_PIN 2  // interrupt associated to pin
#define DIGITS_SIZE   6  // this refers to interrupt pin

#define WARM_UP_TIME  30000
#define DEBOUNCE_TIME 700

#define SLAVE_ADDRESS 1  // address of slave (single slave scenario)

#define CHIPSELECT    4
#define FILENAME "datalog.csv"  // where data is saved

#define CSV_DELIM ','

#define SS_CHECK    0x00
#define SS_WRBIN    0x00
#define SS_WRVAL    0x01
#define SS_WVAL     0x01
#define SS_ACK      0x00
#define SS_NO_ACK   0x01

#define intToByteArray(i) static_cast<char*>(static_cast<void*>(&i))
#define charDtoInt(c) (int)(c - 48) // will only be correct for decimals
#endif
