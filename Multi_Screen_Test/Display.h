#ifndef Display_h
#define Display_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <Adafruit_ST7735.h>

class Display{
  public:
   Adafruit_ST7735 tft;
   Display();

  private:
   int CS;
   int DC;
   int RST;

   void initialize(int c, int d, int r);
   
};


#endif
