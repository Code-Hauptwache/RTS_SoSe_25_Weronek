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

// Timing constants
const unsigned long LIGHT_ON_DURATION = 2;  // 2ms light-on phase
const unsigned long STEP_DURATION = 60;  // 60.5ms rounded to 60ms for simplicity

// State variables
bool isPaused = false;
bool lastButtonState = HIGH;  // Using pull-up resistor, so HIGH is not pressed
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50ms debounce time

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH);  // Ensure all LEDs are initially off
  }
  
  // Initialize button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Check button state for pause functionality
  checkButton();
  
  // If not paused, run the approach lights sequence
  if (!isPaused) {
    runApproachLightsSequence();
  }
}

void checkButton() {
  while (digitalRead(BUTTON_PIN) == LOW)
  {

  }
}

void runApproachLightsSequence() {
  // Run through each LED in sequence
  for (int i = 0; i < NUM_LEDS; i++) {
    // Turn on current LED
    digitalWrite(LED_PINS[i], LOW);
    
    // Keep LED on for the light-on duration
    delay(LIGHT_ON_DURATION);
    
    // Turn off current LED
    digitalWrite(LED_PINS[i], HIGH);
    
    // Wait for the step duration before moving to the next LED
    // but check if button was pressed during this time
    unsigned long startWaitTime = millis();
    while (millis() - startWaitTime < STEP_DURATION) {
      checkButton();
      if (isPaused) {
        return;  // Exit the function if paused
      }
    }
  }
  
  // Wait one more step duration after the last LED
  unsigned long startWaitTime = millis();
  while (millis() - startWaitTime < STEP_DURATION) {
    checkButton();
    if (isPaused) {
      return;  // Exit the function if paused
    }
  }
}