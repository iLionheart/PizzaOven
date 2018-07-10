#include "Fader.h"

Display::Display()
{
}

void Display::initialize(int c, int d, int r)
{
  this.CS = c;
  this.DC = d;
  this.RST = r;
  this.tft = Adafruit_ST7735(CS, DC, RST);
}

