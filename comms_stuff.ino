/*
  People counter
  Functions pertaining communication (Serial and I2C)
*/
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
  Serial.println("Wire event request: nothing yet");
  interrupts();
}

void sendSimpleData(){
  /* Send straight data over i2c, no header */
  byte byteArray[4];
  byteArray[0] = (int)((counter >> 24) & 0xFF);
  byteArray[1] = (int)((counter >> 16) & 0xFF);
  byteArray[2] = (int)((counter >> 8)  & 0XFF);
  byteArray[3] = (int)((counter        & 0XFF));

  Serial.println("Sending data...");
  Wire.beginTransmission(SLAVE_ADDRESS); // transmit to device #8
  for (int i = 0; i < 4; i++) {
    Wire.write(byteArray[i]);
  }
  byte stat = Wire.endTransmission();

  if (stat == 0) {
    Serial.print("I2C transmission OK: ");
    Serial.println(counter);
  } else {
    Serial.print("I2C transmission failed: ");
    Serial.print(stat);
  }
}

void sendData(){
  /* Send data over i2c */
  noInterrupts();
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(SS_CHECK);                 // check byte
  Wire.write(SS_WRBIN);                 // control byte
  Wire.write(SS_ACK);                   // ACK byte
  Wire.write(intToByteArray(counter));  // send Value
  Wire.endTransmission();

  Serial.print("Sent: ");  // send same value over serial
  Serial.println(counter);
  interrupts();
}
