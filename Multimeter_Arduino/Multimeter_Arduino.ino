
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 45


#define XPOS 0
#define YPOS 1
#define DELTAY 2



int pauza=300; //pause
int raw= 0;
float Vin= 0;
float Vout= 0;
float VOLin=0;
float VOLout= 0;
float R1= 7500.0f;
float R2= 0;
float R3 = 30000.0; 
float R4 = 7500.0; 

float vout2 = 0.00;
float vin2 = 0.00;
float res1 = 100000.00; // resistance of R1 (100K) 
float res2 = 10000.00; // resistance of R2 (10K) 
int val = 0;
float buffer= 0;
const int Cap_Out = A2;
const int Cap_IN = A3;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;

int x = 84;
int y = 803;
int t = 500;
int yCounter = 0;
int yPosition = 0;
int readings[DISPLAY_WIDTH+1];



void setup()   {  
           
Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
   pinMode(3,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(Cap_Out, OUTPUT);
  pinMode(Cap_IN, OUTPUT);
  attachInterrupt(1, pressed, FALLING);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.print("ForbiddenBit");
  display.setCursor(60,48);
  display.print(".com");


display.display();
  delay(100);
  display.clearDisplay();
display.display();
}
int mmax=1; //max
int mmin=1024; // min
int button=0;
int mode=0;//variable for debouncing button
unsigned long numberOfTimes=0; //number of times
unsigned long sum=0;
int ave=0; //average
int pulse=125; //starting PWM
unsigned long m=0;
void loop()
{

 
  
  if(mode==0)
  { // ------ Volt---------

     if(digitalRead(4)==0) //analoog read 
  { delay(100); mmin=1024; mmax=0; numberOfTimes=0; sum=0; ave=0;}
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0,12);
  display.setTextSize(1);
 
  display.print("[0] Voltage:");
  display.setCursor(95,0);
  
  int value=analogRead(A0);
  
  display.setFont();

  raw= analogRead(A1);
     VOLout = (raw * 5.0) / 1024.0; 
   VOLin = VOLout / (R4/(R3+R4)); 
  
  display.setFont(&FreeSans18pt7b);
 
   display.setCursor(0,62);
   display.print(VOLin);
   display.setCursor(90,62);
   display.print("V");
   delay(500);
   display.display();

  }

if(mode==1)
  { // -------- Analog Read -----------------------

     if(digitalRead(4)==0) //analoog read 
  { delay(100); mmin=1024; mmax=0; numberOfTimes=0; sum=0; ave=0;}
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0,12);
  display.setTextSize(1);
 
  display.print("[1]Analog Read:");
  display.setCursor(95,10);
  
  int value=analogRead(A1);
  
  display.setFont();

  raw= analogRead(A1);
 
  
  display.setFont(&FreeSans18pt7b);
 
   display.setCursor(0,62);
   display.print(raw);
   display.setTextSize(0);
   display.setFont(&FreeSans9pt7b);
   display.setCursor(80,62);
   display.print("Value");
   
   display.display();

  }


  
  if(mode==2)
  {// --------------- ohm meter ---------------
   display.clearDisplay(); 
   display.setFont(&FreeSans9pt7b);
   
   display.setCursor(0,12);
   display.print("[2] Ohms:");


raw= analogRead(A0);
if(raw){
Vin=readVcc()/1000.0;
buffer= raw * Vin;
Vout= (buffer)/1024.0;
buffer= (Vin/Vout) -1;
R2= R1 * buffer;

display.setTextSize(1);
display.setFont(&FreeSans18pt7b);
 
   display.setCursor(0,62);
   display.print(R2);
   display.display();
}
else{
  
display.setTextSize(1);
display.setFont(&FreeSans18pt7b);
  display.setCursor(0,62);
   display.print("WAIT");
   display.display();
   delay(pauza);
}
   

   delay(pauza);
   }


  if(mode==3)
  {//continuiti
   display.clearDisplay();
   //display.drawBitmap(96, -4,  continu, 32, 32, 1);
      display.setFont(&FreeSans9pt7b);
   display.setCursor(0,12);
   display.print("[3]Continuity:");
   display.setFont(&FreeSans18pt7b);
 
   display.setCursor(0,62);
  
   
   raw= analogRead(A0);
 
  Vin=readVcc()/1000.0;
  buffer= raw * Vin;
  Vout= (buffer)/1024.0;
  float rez=Vin-Vout;
    if(rez<1)
      {
        tone(6,2250);
         display.print("Yes");
         digitalWrite(13,1);
      }
     if(rez>1)
     {
     noTone(6);
     digitalWrite(13,0);
     display.print("No");
     }
     display.display();
    }
      
  if(mode==4) // ----dioda drop
  {
   display.clearDisplay();
   //display.drawBitmap(96, 0,  dioda, 32, 32, 1);
   display.setFont(&FreeSans9pt7b);
 
   display.setCursor(0,12);
   display.print("[4]Voltage Drop:");

     
   display.setCursor(0,30);
   display.print("Diode:");
   raw= analogRead(A0);  
 
  Vin=readVcc()/1000.0;
  buffer= raw * Vin;
  Vout= (buffer)/1024.0;

    display.setFont(&FreeSans18pt7b);
 
   display.setCursor(0,63);
   if(Vout==0){
    display.print("0");}
   else{
   display.print(Vin-Vout);}
    display.display();
     delay(500);
  }   

if(mode==5)
  {//  ------   Capacitor ---------

   display.clearDisplay();
   //display.drawBitmap(96, 0,  dioda, 32, 32, 1);
   display.setFont(&FreeSans9pt7b);
 
   display.setCursor(0,12);
   display.print("[5]Capacitor:");
   display.display();
   
   pinMode(Cap_IN, INPUT);
    digitalWrite(Cap_Out, HIGH);
    int val = analogRead(Cap_IN);
    digitalWrite(Cap_Out, LOW);

    if (val < 1000)
    {
      pinMode(Cap_IN, OUTPUT);

      float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);

      display.clearDisplay();
      display.setFont(&FreeSans9pt7b);
   display.setCursor(0,12);
   display.print("[3]Continuity:");
   display.setFont(&FreeSans18pt7b);
 
    }
    else
    {
      pinMode(Cap_IN, OUTPUT);
      delay(1);
      pinMode(Cap_Out, INPUT_PULLUP);
      unsigned long u1 = micros();
      unsigned long t;
      int digVal;

      do
      {
        digVal = digitalRead(Cap_Out);
        unsigned long u2 = micros();
        t = u2 > u1 ? u2 - u1 : u1 - u2;
      } while ((digVal < 1) && (t < 400000L));

      pinMode(Cap_Out, INPUT);  
      val = analogRead(Cap_Out);
      digitalWrite(Cap_IN, HIGH);
      int dischargeTime = (int)(t / 1000L) * 5;
      delay(dischargeTime);   
      pinMode(Cap_Out, OUTPUT);  
      digitalWrite(Cap_Out, LOW);
      digitalWrite(Cap_IN, LOW);

      float capacitance = -(float)t / R_PULLUP
                              / log(1.0 - (float)val / (float)MAX_ADC_VALUE);

      Serial.print(F("Capacitance Value = "));
      if (capacitance > 1000.0)
      {
        display.setCursor(20,42);
        //display.setFont(&FreeSans9pt7b);
        display.print(capacitance / 1000.0,2);
        display.print(F(" uF"));
        Serial.print(capacitance / 1000.0,2);
      }
      else
      {
        display.setCursor(20,42);
        //display.setFont(&FreeSans18pt7b);
        display.print(capacitance, 2);
        display.print(F(" nF"));
        Serial.print(capacitance, 2);
      }

      Serial.print(F(" ("));
      Serial.print(digVal == 1 ? F("Normal") : F("HighVal"));
      Serial.print(F(", t= "));
      Serial.print(t);
      Serial.print(F(" us, ADC= "));
      Serial.print(val);
      Serial.println(F(")"));
      
      display.display();
      delay(1000);
      
    }
    while (millis() % 1000 != 0);   
    }

 if(mode==6) // pwm generator
 {

  int value=analogRead(A1);
  pulse=(value/4.01);
  
// int lineWidth2=0;
  analogWrite(6,pulse);
  display.clearDisplay();

 display.setFont(&FreeSans9pt7b);
 
   display.setCursor(0,12);
   display.print("[6] PWM:");

     
   display.setCursor(0,28);
   display.print("Width:");
  display.setFont(&FreeSans18pt7b);
   display.setCursor(0,60);
   display.print(pulse);
//   lineWidth2= map(pulse,0,255,0,128);
   //display.drawLine(0,63,lineWidth2,63,1);
   display.display();
  }   
/*  
if(mode==6) //-------- osciloscope -------------
  {
    display.clearDisplay();
  for(yCounter = 0; yCounter < x; yCounter++)
  {                             
    yPosition = (analogRead(A3)*31)/y;
    readings[yCounter] = yPosition;
    delayMicroseconds(t);
  } 
  for(yCounter = 84; yCounter >= x; yCounter--)
  {              
     readings[yCounter] = readings[yCounter-x];
  }
  for(yCounter = 1; yCounter <= 84; yCounter++)
  {
    display.drawLine(yCounter-1, (DISPLAY_HEIGHT-1)-readings[yCounter-1], yCounter, (DISPLAY_HEIGHT-1)-readings[yCounter], BLACK);
     
  }
   
  
  
  display.drawLine( 10, 0, 10, DISPLAY_HEIGHT-1, BLACK);
  display.drawLine( 7, DISPLAY_HEIGHT-1, 10, DISPLAY_HEIGHT-1, BLACK);
  display.drawLine( 7, (DISPLAY_HEIGHT-1)-(6.2 *1023/y), 10, (DISPLAY_HEIGHT-1)-(6.2 *1023/y), BLACK);
  display.drawLine( 7, (DISPLAY_HEIGHT-1)-(12.4 *1023/y), 10, (DISPLAY_HEIGHT-1)-(12.4 *1023/y), BLACK);
  display.drawLine( 7, (DISPLAY_HEIGHT-1)-(18.6 *1023/y), 10, (DISPLAY_HEIGHT-1)-(18.6 *1023/y), BLACK);
  display.drawLine( 7, (DISPLAY_HEIGHT-1)-(24.8 *1023/y), 10, (DISPLAY_HEIGHT-1)-(24.8 *1023/y), BLACK);
  display.drawLine( 7, (DISPLAY_HEIGHT-1)-(31 *1023/y), 10, (DISPLAY_HEIGHT-1)-(31 *1023/y), BLACK);
  display.setCursor(0,DISPLAY_HEIGHT-4);
  display.print(0);
  display.setCursor(0,((DISPLAY_HEIGHT-1)-(6.2 *1023/y))-3);
  display.print(1);
  display.setCursor(0,((DISPLAY_HEIGHT-1)-(12.4 *1023/y))-3);
  display.print(2);
  display.setCursor(0,((DISPLAY_HEIGHT-1)-(18.6 *1023/y))-3);
  display.print(3);
  display.setCursor(0,((DISPLAY_HEIGHT-1)-(24.8 *1023/y))-3);
  display.print(4);
  display.setCursor(0,((DISPLAY_HEIGHT-1)-(31 *1023/y))-3);
  display.print(5);
   
  display.display();
    }


  
}*/
}
void pressed() //midle button presed, changing modes
{

 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 220) 
 {
  mode++;
   tone(6,2250,50);
   if(mode>6)
   mode=0;
 }
 last_interrupt_time = interrupt_time;
  }

  
long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
