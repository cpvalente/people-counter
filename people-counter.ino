#include "DEFINITIONS.h"

// ================ | COMMS
byte comm_header[] = {0, 0, 0};
char digits[DIGITS_SIZE];


// ================ | DATA
File myFile;
unsigned int counter = 0;

// ================ | SENSOR
byte value = 0; // NIU

// ================ | TIME
unsigned long timer = 0;
unsigned long wait;

void setup() {

  // ================ | INIT Comms - I2C
  Wire.begin();                   // join i2c bus
  Wire.onReceive(receiveEvent);   // register event handler
  Wire.onRequest(requestEvent);

  // ================ | INIT Comms - Serial Debug
  Serial.begin(9600);
  while (!Serial){
    ; // Wait for connection
  }
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
  timer = millis();
  wait = 100; // initial warm up time for sensors

}

void loop() {
  // nothing here yet
}

void motionDetected() {
  /* Handler for digital interrupt from PIR sensor */
  if (millis() - timer < wait) return;  // avoid double readings

  counter++;      // increment counter

  timer = millis();
  wait = 7000;      // wait between sensor readings once up

  Serial.println("Movement Detected");
  Serial.print("Count: ");
  Serial.println(lastValue);

  Serial.print("Digits: ");
  Serial.println(digits);

  //send_data();
}

void receiveEvent(int n){
  /* Handler for when a message is received */
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character
    Serial.print(c);
  }

  int x = Wire.read();           // receive byte as an integer
  Serial.println(x);
}

void requestEvent(){
  /* Handler for request events */
  Wire.write("Wire event request: nothing yet");
  Serial.println("Wire event request: nothing yet");
}

void sendData(){
  /* Send data over i2c */
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(byte(0x00));        // instruction byte
  Wire.write(digits);            // send Value
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

void writeDataFile(String s){
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
