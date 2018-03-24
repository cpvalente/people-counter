# people-counter

  People Counter - Sender Node
  == Program counts events from PIR sensor
  == periodically + onChange sends value over i2c
  == programmed to run on Adafruit Adalogger 32u4

  Carlos Valente 15.03.18

  =======| TODO
  - Send information to displays
  -- Build i2c packets
  - Implement timers
  -- update display
  -- stream values
  - Add file header

  - Add hardware listing to README

  =======| Implemented
  - SD operations
  -- Write new value to CSV (a bit silly without RTC, implemented anyway)
  -- Read value from SD if it exists
  - Serial for debug and comm
  - Value from digitalInterrupt
  - Handling timing rollover https://playground.arduino.cc/Code/TimingRollover

  =======| Extend
  - Better handle interval between measurements
  - DEBUG mode
  - Add RTC

  =======| EXTEND
  - RTC
  - Communications https://github.com/adafruit/Adalight/blob/master/Arduino/LEDstream/LEDstream.pde

  =======| NOTES
  - Serial Events not working with adalogger
  - Events have noInterrupt()
  - Arduino SD library returned false readings after certain number of entries (~400)
