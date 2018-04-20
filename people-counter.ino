/*
  People counter
  Working but not finished
*/

#include "DEFINITIONS.h"

// ================ | DATA LOGGING
File logFile;
unsigned long counter = 0;

// ================ | I2C
extern uint16_t twi_readFrom_timeout;
extern uint16_t twi_writeTo_timeout;
extern bool twi_readFrom_wait;
extern bool twi_writeTo_wait;

// ================ | TIMERS
long timerPIR;
long lastBroadcast;

// ================ | AUX
bool bSafeTrigger = false;


void setup() {
  // ================ | INIT Comms - I2C
  Wire.begin();                    // join i2c bus
  twi_readFrom_wait = false;       // Suppress twi_readFrom() waiting loop
  twi_writeTo_wait = false;        // Suppress twi_writeTo() waiting loop

  Wire.onReceive(receiveEvent);    // register event handlers
  Wire.onRequest(requestEvent);

  // ================ | INIT Comms - Serial Debug
  Serial.begin(9600);
  delay(1000);
  Serial.println("PEOPLE COUNTER STARTED");

  // ================ | INIT DATA
  initFromSD();
  Serial.print("Starting with counter: ");
  Serial.println(counter);

  // ================ | INIT SENSOR
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_PIN, motionDetected, HIGH);

  // ================ | INIT Aux Variables
  timerPIR = millis() + WARM_UP_TIME;
}

void loop() {
  /* Transmit values every BROADCAST_TIME */
  if (millis() - lastBroadcast >= BROADCAST_TIME){
    sendSimpleData();
    lastBroadcast = millis();
  }
}

void motionDetected() {
  /* Handler for digital interrupt from PIR sensor */
  if ((long)millis() - timerPIR < 0) // avoid double readings
    return;

  if (!bSafeTrigger) {              // Good readings on second high
    bSafeTrigger = true;
    return;
  }

  noInterrupts();
  bSafeTrigger = false;
  counter++;                        // increment counter

  Serial.println("Movement Detected");
  Serial.print("Count: ");
  Serial.println(counter);

  sendSimpleData();                 // data to i2c
  logToFile(counter);               // log event to SD
  timerPIR = millis() + DEBOUNCE_TIME;
  interrupts();
}

inline long iPow(int base, int exp){
  /* long based pow(), always returns int */
  long result = 1;
  while (exp){
    if (exp & 1)
      result *= base;
    exp /= 2;
    base *= base;
  }
  return result;
}
