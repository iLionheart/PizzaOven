#ifndef Display_h
#define Display_h

#include "Arduino.h"

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

class Display{
  public:
   Adafruit_ST7735 tft = Adafruit_ST7735(12,13,14);
   Display();
   int CS;
   int DC;
   int RST;

   void initialize(int c, int d, int r);
   
};


#endif
