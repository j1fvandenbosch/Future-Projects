#include "FastLED.h"

#define NUM_LEDS 45
#define LED_PIN 2
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  // Set the 45 proximity sensors pins as inputs, from digital pin 3 to pin 48
  for (int pinNo = 0 + 3; pinNo <= 45 + 3; pinNo++) {
    pinMode(pinNo, INPUT);
  }
}

void loop() {
  for (int pinNo = 0; pinNo <= NUM_LEDS-1; pinNo++) {
    leds[pinNo] = CRGB( 0, 255, 0);    // Set all 45 LEDs to green color 
    // If an object is detected on top of the particular sensor, turn on the particular led
    if ( digitalRead(pinNo + 3) == LOW ) {
      leds[pinNo] = CRGB( 0, 0, 255); // Set the reactive LED to bluee
    }
  }
  FastLED.show(); // Update the LEDs
  delay(20);
}
