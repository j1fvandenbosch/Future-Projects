#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET          A4

#define SSD1306_WHITE 1
#define SSD1306_BLACK 0
#define SSD1306_INVERSE 2

Adafruit_SSD1306 display(OLED_RESET);

int analogInput = A1;

void setup() {
  pinMode(analogInput, INPUT);

  Serial.begin(9600);
  Serial.println("DC VOLTMETER");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.display();
  display.clearDisplay();

  display.display();

  display.drawRect(0, 0,  128 , 16, SSD1306_WHITE);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(18, 4);
  display.println("- DC VOLTMETER -");
  display.display();
}

float vout = 0.0;
float vin = 0.0;

float R1 = 30000.0;
float R2 = 7500.0;

int value = 0;

void loop() {

  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  Serial.print("INPUT Voltage= ");
  Serial.println(vin, 2);

  display.setTextSize(1);
  display.setCursor(0, 25);
  display.println("INPUT Voltage");

  display.setTextSize(2);
  display.setCursor(20, 40);
  display.println(vin, 2);
  display.setCursor(80, 40);
  display.println("V");
  display.display();

  delay(2000);


}

