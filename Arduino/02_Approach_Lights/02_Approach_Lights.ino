// Zakria Boujana - Approaach Lights
#include <Arduino.h>

// Define LED pins
const int LED1 = 5;
const int LED2 = 6;
const int LED3 = 7;
const int LED4 = 8;
const int LED5 = 9;
const int LED6 = 10;
const int LED7 = 11;
const int LED8 = 12;

// Define button pin
const int BUTTON_PIN = 2;

// Store LED pins in an array for easier access
const int LED_PINS[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
const int NUM_LEDS = 8;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {  
  for (int i = 0; i < NUM_LEDS; i++) {
    while (digitalRead(BUTTON_PIN) == LOW) {}
    digitalWrite(LED_PINS[i], LOW);
    delay(2);
    digitalWrite(LED_PINS[i], HIGH);
    delay(60);
  }
  delay(60);
}