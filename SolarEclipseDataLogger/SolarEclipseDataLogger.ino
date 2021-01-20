#include <SPI.h>
#include <SD.h>
#include <Wire.h> // Required for RTC
#include <Time.h> // Required for RTC
#include <DS1307RTC.h> // Required for RTC
#include "DHT.h" // Required for DHT11

#define SD_CS  10 // Chip select on SD card
#define DHTPIN 2  // Data pin on DHT11
#define DHTTYPE DHT11   // DHT 11
#define LIGHTPIN 0  // Photoresitor pin

File dataFile; // File to do file operations on
tmElements_t RealTimeClock; // A time variable to hold RTC values
DHT dht(DHTPIN, DHTTYPE); // Instantiate DHT device
String dataString;

void setup() 
{
  Serial.begin(9600);
  SD.begin(SD_CS);
  dht.begin();

}

void loop() 
{
  RTC.read(RealTimeClock);
  dataFile = SD.open("data.txt", FILE_WRITE);
  dataString = String(RealTimeClock.Hour) + ":" + String(RealTimeClock.Minute) + ":" + String(RealTimeClock.Second) + "," + String(dht.readTemperature()) + "," + String(dht.readHumidity()) + "," + String(analogRead(LIGHTPIN));
  dataFile.println(dataString);
  dataFile.close(); 
  Serial.println(dataString);
  delay(1000);
}

