/*
 * This is a test of the arduino equivalent of the pizza oven project.
 * This code uses the Adafruit Graphics library with the Temperature sensors and IR sensor
 */

/*
 * this is a comment about buttface. Its a great word that, in my opinion, should be used more often
 */

 
#include <Adafruit_GFX.h>//core graphics
#include <Adafruit_ST7735.h>//hardware-specific library
#include <SPI.h>//the spi library

/*
 * Define the pins for the SPI not already defined by the hardware
 */
#define TFT_CS    10
#define TFT_RST   9
#define TFT_DC    8

/*
 * Setting up the TFT using the library
 */
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int IR_ADC_PIN = A0;
int TEMP_ADC_PIN = A1;
int IR_value = 0;
int TEMP_value = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Test of Pizza oven Code");

  tft.initR(INITR_BLACKTAB);

  Serial.print("Initialized");
  tft.fillScreen(ST7735_BLACK);
  

}

void loop() {
  IR_value = analogRead(IR_ADC_PIN);
  TEMP_value = analogRead(TEMP_ADC_PIN);
//  float volts = IR_value*0.0032226563;
//  float distance = 65*pow(volts, -1.10);
  tft.print(IR_value);
  tft.println(": IR value");
  tft.print(TEMP_value);
  tft.println(": Temp value");
  delay(1000);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);
}
