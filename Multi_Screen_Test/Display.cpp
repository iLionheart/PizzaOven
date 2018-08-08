#include "Display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

Display::Display()
{
}

void Display::initialize(int c, int d, int r)
{
  CS = c;
  DC = d;
  RST = r;
  this->tft = Adafruit_ST7735(CS, DC, RST);
}
