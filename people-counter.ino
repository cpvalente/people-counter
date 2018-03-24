#include "DEFINITIONS.h"

// ================ | COMMS
byte comm_header[] = {0x00, 0x00, 0x00};
char digits[DIGITS_SIZE];

// ================ | DATA LOGGING
File logFile;
long counter = 0;

// ================ | TIMERS
unsigned long tPIR;

void setup() {
  // ================ | INIT Comms - I2C
  Wire.begin();                      // join i2c bus
  Wire.onReceive(receiveEvent);      // register event handlers
  Wire.onRequest(requestEvent);

  // ================ | INIT Comms - Serial Debug
  Serial.begin(38400);
  while (!Serial){
      ;             // Wait for connection
  }
  Serial.println("STARTED");

  // ================ | INIT DATA
  initFromSD();

  // ================ | INIT SENSOR
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_PIN, motionDetected, HIGH);

  // ================ | INIT Aux Variables
  tPIR = millis() + WARM_UP_TIME; // initial warm up time for sensors
}

void loop() {
  // nothing here yet
}

void motionDetected() {
  /* Handler for digital interrupt from PIR sensor */
  if (millis() - tPIR < 0) return; // avoid double readings

  noInterrupts();
  counter++;                       // increment counter

  tPIR = millis() + DEBOUNCE_TIME; // wait between sensor readings once up

  Serial.println("Movement Detected");
  Serial.print("Count: ");
  Serial.println(counter);

  Serial.print("Digits: ");
  Serial.println(digits);

  sendData();          // data to i2c
  logToFile(counter);  // log event to SD
  interrupts();
}

inline long iPow(int base, int exp){
  /* long based pow(), always returns int */
  long result = 1;
  while (exp){
    if (exp & 1) // what is this??
      result *= base;
    exp /= 2;
    base *= base;
  }
  return result;
}

void receiveEvent(int n){
  /* Handler for when a message is received */
  noInterrupts();
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character
    Serial.print(c);
  }

  int x = Wire.read();           // receive byte as an integer
  Serial.println(x);
  interrupts();
}

void requestEvent(){
  /* Handler for request events */
  noInterrupts();
  Wire.write("Wire event request: nothing yet");
  Serial.println("Wire event request: nothing yet");
  interrupts();
}

void sendData(){
  /* Send data over i2c */
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(SS_CHECK);                 // check byte
  Wire.write(SS_WRBIN);                 // control byte
  Wire.write(SS_ACK);                   // ACK byte
  Wire.write(intToByteArray(counter));  // send Value
  Wire.endTransmission();

  Serial.print("Sent: ");  // send same value over serial
  Serial.println(counter);
}

void initFromSD() {
    /* Reads last int from SD or creates new file */
    if (SD.begin(CHIPSELECT)) {      // connected to SD
        logFile = SD.open(FILENAME, FILE_WRITE);
        counter = readLast();        // Read last int
        if (counter == -1)           // Something went wrong
            counter = 0;
    } else {                         // cannot connect to SD
      Serial.println("Card init. failed or not present");
      counter = 0;
    }
}


long readLast(){
  /* Read data from file */
  /*
    We know the last digit will start 8 char from end
    (EOF + endline + 6 digits)
    Anyway, we will check it manually for peace of mind
  */
  long val = -1;
  logFile = SD.open(FILENAME, FILE_READ);

  if (!logFile) return val;
  else {    // file opened successfully
    char c;
    int pointer = 0;

    while(true){ // set pointer to last decimal
      logFile.seek( logFile.size() - pointer );
      c = logFile.read();
      if (isDigit(c)) break;
      pointer++;
    }

    int dig = 0;
    val = 0;

    while(true){ // go again to get digits
      if (isDigit(c)) {
        val = val + charDtoInt(c) * iPow(10, dig);
      } else break;
      dig++;
      pointer++;
      logFile.seek(logFile.size() - pointer);
      c = logFile.read();
    }
  }

  logFile.close();
  return val;
}

void logToFile(long number){
  /* Writes number to SD in CSV format */
  char logThis[6];
  sprintf(logThis, "%06d", number);
  logFile = SD.open(FILENAME, FILE_WRITE);
  if (logFile) {              // Check for previously written file
    logFile.print("RTC");     // Placeholder
    logFile.print(CSV_DELIM);
    logFile.println(logThis);
    logFile.close();
  } else {
    Serial.println("Could not read or create file");
  }
}
