#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <Wire.h>       // i2c communications
#include <SPI.h>        // SD
#include <SD.h>         // SD

#define SENSOR_PIN    0  // sensor pin
#define INTERRUPT_PIN 2  // interrupt associated to pin
#define DIGITS_SIZE   6  // this refers to interrupt pin

#define WARM_UP_TIME  30000
#define DEBOUNCE_TIME 700

#define SLAVE_ADDRESS 1  // address of slave (single slave scenario)

#define FILENAME "datalog.dat"  // where data is saved
#define CHIPSELECT    4

#endif
