/* 
Example Timer1 Interrupt
Flash LED every second
*/

/*
 * this is me changing the file
 */
 

int timer1_counter;
int t1=0;
int t2;
void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  t2 = millis();
  TCNT1 = timer1_counter;   // preload timer
  Serial.print(t2 - t1);
  Serial.println("");
  t1 = t2;
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

void loop()
{
  // your program here...
}
