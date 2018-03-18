# people-counter

/* ================ ================ ================

  People Counter - Sender Node
  == Program counts events from PIR sensor
  == periodically + onChange sends value over i2c
  == programmed to run on Adafruit Adalogger 32u4

  Carlos Valente 15.03.18

  =======| TODO
  - Send information to displays
  -- Build i2c packets
  - SD operations
  -- Read value from SD if it exists
  -- Write new value
  - Send values periodically

  - Add hardware listing to README

  =======| Implemented
  - Serial for debug and comm
  - Value from digitalInterrupt
  - Handling timing rollover https://playground.arduino.cc/Code/TimingRollover

  =======| Extend
  - Better handle interval between measurements
  - Add RTC

  =======| EXTEND
  - RTC
  - Communications https://github.com/adafruit/Adalight/blob/master/Arduino/LEDstream/LEDstream.pde

  ================ ================ ================ */
