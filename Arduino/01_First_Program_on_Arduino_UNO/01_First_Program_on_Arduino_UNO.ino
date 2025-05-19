#include <Arduino.h>

// Define LED pins
const int LED1 = 7;  
const int LED2 = 6;  
const int LED3 = 5;  
const int LED4 = 4;  

void setup() {
  // Initialize all LED pins as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  // Initially turn off all LEDs
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {
  // Pattern 1: Sequential blinking (one after another)
  sequentialBlink(300);  // 300ms delay between actions
}

// Function for sequential blinking
void sequentialBlink(int delayTime) {
  // Turn on and off each LED in sequence
  digitalWrite(LED1, HIGH);
  delay(delayTime);
  digitalWrite(LED2, HIGH);
  delay(delayTime);
  digitalWrite(LED3, HIGH);
  delay(delayTime);
  digitalWrite(LED4, HIGH);  
  delay(delayTime);
  
  digitalWrite(LED2, LOW);
  delay(delayTime);
  digitalWrite(LED4, LOW);
  delay(delayTime);
  digitalWrite(LED3, LOW);
  delay(delayTime);
  digitalWrite(LED1, LOW);
  delay(delayTime);  // Pause before next pattern
  
}