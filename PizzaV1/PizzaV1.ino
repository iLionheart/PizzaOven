

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_RST       9
#define TFT_DC        8
#define CABINET_SIZE  6

int IR_MAX = 300;

class Shelf{
  public:
  int ADC_T;
  int ADC_IR;
  int ID;
  int Temp;
  int IR;
  int Order;
  Adafruit_ST7735 tft;

  Shelf(int TFT_CS, int I, int T, int Laser){
    tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    ID = I;
    ADC_T = T;
    ADC_IR - Laser;
    InitDisplay();
  }

  void InitDisplay(){
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
  }
  
  int getID(){return ID;}

  int getOrder(){return Order;}
  
  int getTemp(){return Temp;}
  
  void checkTemp(){
    int reading = analogRead(ADC_T);
    float V = reading * 5.0;
    V /= 1024.0;
    float C = (V - 0.5) * 100;
    float F = (C * 9.0 / 5.0) + 32;
    Temp = F;
  }
  
  bool getIR(){
    if(analogRead(ADC_IR) >= IR_MAX){
      return true;
    }
    return false;
  }

}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
