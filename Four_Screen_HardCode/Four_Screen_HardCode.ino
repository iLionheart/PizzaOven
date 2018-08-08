#include <dht.h>

#include <SPI.h>
#include <TFT.h>
#include <math.h>

#define TFT_RS 9
#define TFT_DC 8
#define DHT11_PIN 35

struct screen
{
  int FIFO;//The first in first out number 
  char FIFOout[2];//The Char array for tft printout for FIFO
  int analogPin;//Analog pin the temp sensor is on
  float dataTemp;//The temperature
  float dataIR;//The IR analog value NOT IMPLEMENTED
  char dataOut[6];//The Char array for tft printout for temperature
  int CS;//The Chip Select Pin number
  TFT S = TFT(1,TFT_DC,TFT_RS);//The TFT Object
};

typedef struct screen Screen;

void initScreens();
float getTemp(Screen*);
void displayData(Screen Array[]);
void changeFIFO(Screen*, int);

dht DHT;//For Testing
/**
 * The array of Screens, change the number (4)
 * if you wish to add more shelves to the cabinet
 */
Screen Shelves[4];
/**
 * The array of FIFO numbers for 
 * reference in the display function.
 * only used for testing at the moment
 */
int FifoN[4];
/**
 * Theoreticle method of keeping track of 
 * FIFO number
 */
int number;

//screens for init
Screen A;
Screen B;
Screen C;
Screen D;

void setup() {
  Serial.begin(115200);
  //reference available voltage
  analogReference(EXTERNAL);
  number = 0;
  FifoN[0] = 2;
  FifoN[1] = 3;
  FifoN[2] = 1;
  FifoN[3] = 4;
  initScreens();
  int i = 0;
}
void loop() { 
  displayData();
}

/**
 * Takes a pointer to a Screen variable
 * and uses the Steinhart Equation to 
 * generate a value for the temperature
 */
float getTemp(Screen* t){
  int adc = analogRead(t->analogPin);
  
  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  
  Vo = adc;
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  t->dataTemp = T;
  return(T);
  
  //use steinhart equation.
  /*
   * Test values
   * c1 = 0.9789298578 * 10^-3
   * c2 = 2.808984118 * 10^-4
   * c3 = 0.000019160845 * 10^-7
   */
}

/**
 * Initializes all screens for use.
 * If you wish to add a shelf, add a
 * new global
 * Screen <name>
 * then use the template below
 * -------------------------------------
  <name>.CS = <Chip Select Pin Number>;
  <name>.analogPin = <Analog Pin Number>;
  <name>.dataTemp = 0;
  <name>.FIFO = NULL;
  <name>.S = TFT(A.CS, TFT_DC, TFT_RS);
  <name>.S.begin();
  <name>.S.setRotation(3);
  <name>.S.setTextSize(2);
  <name>.S.background(0,0,0);
  <name>.S.stroke(255,255,255);
  <name>.S.stroke(ST7735_WHITE);
 * -------------------------------------
 * 
 * Then after, add it to the Shelves array
 * 
 * Shelves[#] = <name>;
 */
void initScreens(){
  
  //Screen A
  A.CS = 17;//sets the Chip select pin
  A.analogPin = A0;//sets the analog pin
  A.dataTemp = 0;//initializes temp to 0
  A.FIFO = NULL;//initializes FIFO to 0
  A.S = TFT(A.CS, TFT_DC, TFT_RS);//initializes the TFT to the proper pins
  A.S.begin();//starts the TFT
  A.S.setRotation(3);//Sets the rotation
  A.S.setTextSize(2);//Sets the text size
  A.S.background(0,0,0);//Sets the background to black
  A.S.stroke(255,255,255);//Sets the stroke to White
  A.S.text("Hello World!",0,0);//Prints "Hello World" //for testing
  A.S.stroke(ST7735_WHITE);//Sets the Stroke to White
  
  //Screen B
  B.CS = 18;
  B.analogPin = A1;
  B.FIFO = NULL;
  B.dataTemp = 0;
  B.S = TFT(B.CS, TFT_DC, TFT_RS);
  B.S.begin();
  B.S.setRotation(3);
  B.S.setTextSize(2);
  B.S.background(0,0,0);
  B.S.stroke(255,255,255);
  B.S.text("Hello World!",0,0);//for testing
  B.S.stroke(ST7735_WHITE);
  
  //Screen C
  C.CS = 19;
  C.analogPin = A2;
  C.FIFO = NULL;
  C.dataTemp = 0;
  C.S = TFT(C.CS, TFT_DC, TFT_RS);
  C.S.begin();
  C.S.setRotation(3);
  C.S.setTextSize(2);
  C.S.background(0,0,0);
  C.S.stroke(255,255,255);
  C.S.text("Hello World!",0,0);//for testing
  C.S.stroke(ST7735_WHITE);
  
  //Screen D
  D.CS = 20;
  D.analogPin = A3;
  D.FIFO = NULL;
  D.dataTemp = 0;
  D.S = TFT(D.CS, TFT_DC, TFT_RS);
  D.S.begin();
  D.S.setRotation(3);
  D.S.setTextSize(2);
  D.S.background(0,0,0);
  D.S.stroke(255,255,255);
  D.S.text("Hello World!",0,0);//for testing
  D.S.stroke(ST7735_WHITE);

  //Add Screens to Shelves array
  Shelves[0] = A;
  Shelves[1] = B;
  Shelves[2] = C;
  Shelves[3] = D;

  for(Screen t: Shelves){
    t.S.fillScreen(ST7735_BLACK);//clears each screen
  }
}

/**
 * Changes the FIFO number using a 
 * pointer to a Screen.
 */
void changeFIFO(Screen* t, int c){
  t->FIFO = c;
}

/**
 * Displays the data for all Screens
 * For the TFT library the data must be in
 * Char Array form to print out.
 */
void displayData(){
  int a = 0;
  number = 0;
  for(Screen t: Shelves){
    
    changeFIFO(&t,FifoN[a]); //This is in here now for testing

      //if the FIFO number has changed, clear previous
      if(t.FIFO != FifoN[a]){
        t.S.fillRect(0,0,66,91,ST7735_CYAN);
      }
      //clear previous temp on screen
      t.S.fillRect(80,40,72,14,ST7735_BLACK);
      
      String dataS;
      String fifoS;
      float T = getTemp(&t);
      dataS = String(t.dataTemp);
      dataS.toCharArray(t.dataOut,6);
      fifoS = String(t.FIFO);
      fifoS.toCharArray(t.FIFOout,2);
      //Print out the new FIFO
      t.S.setTextSize(13);
      t.S.text(t.FIFOout,0,0);
      //Print out the new Temp
      t.S.setTextSize(2);
      t.S.text(t.dataOut,80,40);
      
      a++;
  }
}

