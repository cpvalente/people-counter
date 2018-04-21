/*
  People counter
  Functions pertaining SD implementation
*/

void initFromSD() {
    /* Reads last int from SD or creates new file */
    noInterrupts();
    Serial.println("Reading SD");
    if (SD.begin(CHIPSELECT)) {      // connected to SD
      Serial.println("Card Initialized");
      counter = 0;
        counter = readLast();        // Read last int
        if (counter == -1)           // Something went wrong
            counter = 0;
    } else {                         // cannot connect to SD
      Serial.println("Card init. failed or not present");
      counter = 0;
    }
    interrupts();
}

long readLast(){
  /* Read data from file
      We know the last digit will start 8 char from end
      (EOF + endline + 6 digits)
      Anyway, we will check it for peace of mind
  */
  long val = -1;
  logFile = SD.open(FILENAME, FILE_WRITE);
  if (logFile.size() <= 0) return val;
  if (!logFile) return val;

  /* File opened successfully*/
  Serial.println("File opened successfully");
  char c;
  int pointer = 0;
  Serial.println("Find last decimal in file");
  while(true){ // set pointer to last decimal
    logFile.seek( logFile.size() - pointer );
    c = logFile.read();
    if (isDigit(c)) break;
    pointer++;
  }

  int dig = 0;
  val = 0;
  Serial.println("Reading digits");

  while(true){ // go again to get digits
    Serial.print(c);
    if (isDigit(c)) {
      val = val + charDtoInt(c) * iPow(10, dig);
    } else break;
    dig++;
    pointer++;
    logFile.seek(logFile.size() - pointer);
    c = logFile.read();
  }
  Serial.println("Finished, closing file");
  logFile.close();
  return val;
}

void logToFile(long number){
  /* Writes number to SD in CSV format */
  char logThis[6];
  sprintf(logThis, "%06d", number); // force 6 digits
  logFile = SD.open(FILENAME, FILE_WRITE);
  if (!logThis) {
    Serial.println("Could not read or create file");
    return;
  }
  Serial.print("Adding entry to file ");
  Serial.println(logThis);
  logFile.print("RTC");         // Placeholder
  logFile.print(CSV_DELIM);
  logFile.println(logThis);     // Value
  logFile.close();
}
