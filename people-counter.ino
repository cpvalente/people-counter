#include "DEFINITIONS.h"

// ================ | COMMS
byte comm_header[] = {0, 0, 0};
char digits[DIGITS_SIZE];

// ================ | DATA
File myFile;
unsigned int counter = 0;

// ================ | SENSOR
byte value = 0; // NIU

// ================ | TIMERS
unsigned long tPIR;

void setup() {

  // ================ | INIT Comms - I2C
  Wire.begin();                   // join i2c bus
  Wire.onReceive(receiveEvent);   // register event handler
  Wire.onRequest(requestEvent);

  // ================ | INIT Comms - Serial Debug
  Serial.begin(38400);
  while (!Serial){ ; } // Wait for connection
  Serial.println("STARTED");

  // ================ | INIT DATA
  if (!SD.begin(CHIPSELECT))
    Serial.println("Card init. failed!");
  else {
    //if (!myFile.exists(FILENAME)) myFile = SD.open(FILENAME. FILE_WRITE);

    File dataFile = SD.open("datalog.txt");

  }

  // ================ | INIT SENSOR
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_PIN, motion_detected, HIGH);

  // ================ | INIT Aux Variables
  tPIR = millis() + WARM_UP_TIME; // initial warm up time for sensors

}

void loop() {
  // nothing here yet
}

void motionDetected() {
  /* Handler for digital interrupt from PIR sensor */

  if (millis() - tPIR < 0) return;  // avoid double readings

  noInterrupts();
  counter++;  // increment counter

  tPIR = millis() + DEBOUNCE_TIME; // wait between sensor readings once up

  Serial.println("Movement Detected");
  Serial.print("Count: ");
  Serial.println(lastValue);

  Serial.print("Digits: ");
  Serial.println(digits);

  //send_data();
  //logToFile();
  interrupts();
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
  Wire.write(byte(0x00));       // check byte
  Wire.write(byte(0x00));       // control byte
  Wire.write(byte(0x00));       // ACK byte
  Wire.write(digits);           // send Value
  Wire.endTransmission();

  Serial.print("Sent: ");       // send same value over serial
  Serial.println(digits);
}

String readDataFile(){
  /* Read data from file */
  File dataFile = SD.open(FILENAME);
  String s = "";

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  } else {
    Serial.println("Couldnt write to SD");
  }

  return s;
}

void logToFile(String s){
  /* Write to SD */
  File dataFile = SD.open(FILENAME, FILE_WRITE);
  String logThis = "";
  //sprintf (logThis, "ENTRY %s")
  if (dataFile) {
    dataFile.println(s);
    dataFile.close();
  } else {
    Serial.println("Couldnt write to file");
  }
}
