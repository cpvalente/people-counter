  # people-counter

  People Counter - Sender Node

  Program detects events from PIR sensor and sends and counter over i2c
  Programmed to be paired with people-seven code

  Programmed to run on Adafruit Adalogger 32u4

  Carlos Valente 25.03.18
  ------

  ## TO-DO
  - Send information to displays
  ⋅⋅* Build i2c packets
  - Implement timers
  ⋅⋅* update display
  ⋅⋅* stream values
  - Add file header

  - Add hardware listing to README

  ## Implemented
  - SD operations
  ⋅⋅* Write new value to CSV (a bit silly without RTC, implemented anyway)
  ⋅⋅* Read value from SD if it exists
  - Serial for debug and comm
  - Value from digitalInterrupt
  - Handling timing rollover

  ## Extend
  - Better handle interval between measurements
  - DEBUG mode
  - Add RTC

  ## EXTEND
  - RTC
  - Communications [AdaLight](https://github.com/adafruit/Adalight/blob/master/Arduino/LEDstream/LEDstream.pde)

  ## NOTES
  - Serial Events not working with adalogger
  - Events have noInterrupt()
  - Arduino SD library returned false readings after certain number of entries (~400)

  ## License

  This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
