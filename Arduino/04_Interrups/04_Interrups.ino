// Zakria Boujana - Interrupts
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

const int LED_PINS[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
const int NUM_LEDS = 8;

volatile bool runningMode = true;
volatile unsigned long lastButtonPress = 0;
volatile bool modeChanged = false;

void setup() {
  Serial.begin(9600);
  Serial.println("System started - Running mode");
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH);
  }

  if (modeChanged) {
    if (runningMode) {
      Serial.println("running ...");
    } else {
      Serial.println("idle ...");
    }
    modeChanged = false;
  }
  
  if (runningMode) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (!runningMode) break;
      
      digitalWrite(LED_PINS[i], LOW);
      for (int j = 0; j < 2; j++) {
        if (!runningMode) break;
        delay(1);
      }
      digitalWrite(LED_PINS[i], HIGH);
      for (int j = 0; j < 60; j++) {
        if (!runningMode) break;
        delay(1);
      }
    }
    for (int j = 0; j < 60; j++) {
      if (!runningMode) break;
      delay(1);
    }
  }
  else {
    digitalWrite(LED_PINS[0], LOW);
    digitalWrite(LED_PINS[NUM_LEDS - 1], LOW);
    for (int i = 1; i < NUM_LEDS - 1; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
    delay(10);
  }
}

void buttonISR() {
  unsigned long currentTime = millis();
  
  // Debounce - only accept button press if 200ms passed
  if (currentTime - lastButtonPress > 200) {
    runningMode = !runningMode;
    modeChanged = true;
    lastButtonPress = currentTime;
  }
}