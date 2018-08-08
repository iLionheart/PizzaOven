#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "Arduino.h"
#include "Display.h"


#define ATFT_CS    17
#define BTFT_CS    18
#define CTFT_CS    19
#define DTFT_CS    20
#define TFT_RST    9
#define TFT_DC    8


//Adafruit_ST7735 tft = Adafruit_ST7735(ATFT_CS, TFT_DC, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(BTFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;
Display Shelves[4];
void setup() {
  Serial.begin(9600);
  Serial.println("Multi ST7735 Display Test");

  Display A = Display();
  Display B = Display();
  Display C = Display();
  Display D = Display();

  A.initialize(ATFT_CS, TFT_DC, TFT_RST);
  B.initialize(BTFT_CS, TFT_DC, TFT_RST);
  C.initialize(CTFT_CS, TFT_DC, TFT_RST);
  D.initialize(DTFT_CS, TFT_DC, TFT_RST);

  Shelves[0] = A;
  Shelves[1] = B;
  Shelves[2] = C;
  Shelves[3] = D;

  for(Display S: Shelves){
    S.tft.initR(INITR_BLACKTAB);
    S.tft.fillScreen(ST7735_BLACK);
  }

  //Init the screens
//  S.tft.initR(INITR_BLACKTAB);
//  S.tft.initR(INITR_BLACKTAB);
//  S.tft.setRotation(1);

  Serial.println("Initialized");
  uint16_t time = millis();
  time = millis()-time;
  Serial.println(time,DEC);
  delay(500);

}

void loop() {

  for(Display S: Shelves){
    S.tft.fillScreen(ST7735_BLACK);
    testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE, S);
    delay(1000);
  
    // S.tft print function!
    tftPrintTest(S);
    delay(4000);
  
    // a single pixel
    tft.drawPixe(S.tft.width()/2, S.tft.height()/2, ST7735_GREEN, S);
    delay(500);
  
    // line draw test
    testlines(ST7735_YELLOW, S);
    delay(500);
  
    // optimized lines
    testfastlines(ST7735_RED, ST7735_BLUE, S);
    delay(500);
  
    testdrawrects(ST7735_GREEN, S);
    delay(500);
  
    testfillrects(ST7735_YELLOW, ST7735_MAGENTA, S);
    delay(500);
  
    S.tft.fillScreen(ST7735_BLACK);
    testfillcircles1(10, ST7735_BLUE, S);
    testdrawcircles1(10, ST7735_WHITE, S);
    delay(500);
  
    testroundrects(S);
    delay(500);
  
    testtriangles(S);
    delay(500);
  
    mediabuttons(S);
    delay(500);
    S.tft.invertDisplay(true);
    delay(500);
    S.tft.invertDisplay(false);
    delay(500);
  }
  for(Display S: Shelves){
    S.tft.fillScreen(ST7735_BLACK);
  }
}

void testlines(uint16_t color, Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < S.tft.width(); x+=6) {
    S.tft.drawLine(0, 0, x, S.tft.height()-1, color);
  }
  for (int16_t y=0; y < S.tft.height(); y+=6) {
    S.tft.drawLine(0, 0, S.tft.width()-1, y, color);
  }

  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < S.tft.width(); x+=6) {
    S.tft.drawLine(S.tft.width()-1, 0, x, S.tft.height()-1, color);
  }
  for (int16_t y=0; y < S.tft.height(); y+=6) {
    S.tft.drawLine(S.tft.width()-1, 0, 0, y, color);
  }

  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < S.tft.width(); x+=6) {
    S.tft.drawLine(0, S.tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < S.tft.height(); y+=6) {
    S.tft.drawLine(0, S.tft.height()-1, S.tft.width()-1, y, color);
  }

  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < S.tft.width(); x+=6) {
    S.tft.drawLine(S.tft.width()-1, S.tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < S.tft.height(); y+=6) {
    S.tft.drawLine(S.tft.width()-1, S.tft.height()-1, 0, y, color);
  }
}

void testdrawtext(char *text, uint16_t color, Display S) {
  S.tft.setCursor(0, 0);
  S.tft.setTextColor(color);
  S.tft.setTextWrap(true);
  S.tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2, Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < S.tft.height(); y+=5) {
    S.tft.drawFastHLine(0, y, S.tft.width(), color1);
  }
  for (int16_t x=0; x < S.tft.width(); x+=5) {
    S.tft.drawFastVLine(x, 0, S.tft.height(), color2);
  }
}

void testdrawrects(uint16_t color, Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < S.tft.width(); x+=6) {
    S.tft.drawRect(S.tft.width()/2 -x/2, S.tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2, Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  for (int16_t x=S.tft.width()-1; x > 6; x-=6) {
    S.tft.fillRect(S.tft.width()/2 -x/2, S.tft.height()/2 -x/2 , x, x, color1);
    S.tft.drawRect(S.tft.width()/2 -x/2, S.tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color, Display S) {
  for (int16_t x=radius; x < S.tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < S.tft.height(); y+=radius*2) {
      S.tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color, Display S) {
  for (int16_t x=0; x < S.tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < S.tft.height()+radius; y+=radius*2) {
      S.tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles(Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = S.tft.width()/2;
  int x = S.tft.height()-1;
  int y = 0;
  int z = S.tft.width();
  for(t = 0 ; t <= 15; t++) {
    S.tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects(Display S) {
  S.tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = S.tft.width()-2;
    int h = S.tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      S.tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest(Display S) {
  S.tft.setTextWrap(false);
  S.tft.fillScreen(ST7735_BLACK);
  S.tft.setCursor(0, 30);
  S.tft.setTextColor(ST7735_RED);
  S.tft.setTextSize(1);
  S.tft.println("Hello World!");
  S.tft.setTextColor(ST7735_YELLOW);
  S.tft.setTextSize(2);
  S.tft.println("Hello World!");
  S.tft.setTextColor(ST7735_GREEN);
  S.tft.setTextSize(3);
  S.tft.println("Hello World!");
  S.tft.setTextColor(ST7735_BLUE);
  S.tft.setTextSize(4);
  S.tft.print(1234.567);
  delay(1500);
  S.tft.setCursor(0, 0);
  S.tft.fillScreen(ST7735_BLACK);
  S.tft.setTextColor(ST7735_WHITE);
  S.tft.setTextSize(0);
  S.tft.println("Hello World!");
  S.tft.setTextSize(1);
  S.tft.setTextColor(ST7735_GREEN);
  S.tft.print(p, 6);
  S.tft.println(" Want pi?");
  S.tft.println(" ");
  S.tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  S.tft.println(" Print HEX!");
  S.tft.println(" ");
  S.tft.setTextColor(ST7735_WHITE);
  S.tft.println("Sketch has been");
  S.tft.println("running for: ");
  S.tft.setTextColor(ST7735_MAGENTA);
  S.tft.print(millis() / 1000);
  S.tft.setTextColor(ST7735_WHITE);
  S.tft.print(" seconds.");
}

void mediabuttons(Display S) {
  // play
  S.tft.fillScreen(ST7735_BLACK);
  S.tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  S.tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  S.tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  S.tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  S.tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  S.tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  S.tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  S.tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  S.tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}

