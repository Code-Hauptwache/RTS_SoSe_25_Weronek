#include <Arduino.h>

const int S1_PIN = 2;  // Button S1
const int S2_PIN = 13; // Button S2

unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long timeDifference = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(S1_PIN, INPUT_PULLUP);
  pinMode(S2_PIN, INPUT_PULLUP);
  
  // Display welcome message
  Serial.println("Hello this is a reaction Test of your name");
  Serial.println("Press S1 to start the test...");
}

void loop() {
  while (digitalRead(S1_PIN) == HIGH) {
    // Do nothing
  }
  
  // Record the first timestamp in microseconds
  time1 = micros();
  
  // Indicate that S1 has been pressed
  Serial.println("S1 pressed! Now press S2...");
  
  while (digitalRead(S2_PIN) == HIGH) {
    // Do nothing
  }
  
  // Record the second timestamp in microseconds
  time2 = micros();
  
  timeDifference = time2 - time1;  
  float timeDifferenceSeconds = timeDifference / 1000000.0;
  
  // Display the results
  Serial.println("\n--- Results ---");
  Serial.print("Time 1 (microseconds): ");
  Serial.println(time1);
  Serial.print("Time 2 (microseconds): ");
  Serial.println(time2);
  Serial.print("Time difference (microseconds): ");
  Serial.println(timeDifference);
  Serial.print("Time difference (seconds): ");
  Serial.println(timeDifferenceSeconds, 6); // Display with 6 decimal places
  
  // Wait for a moment before allowing another test
  Serial.println("\nWaiting 3 seconds before next test...");
  delay(3000);
  
  // Reset for the next test
  Serial.println("Press S1 to start a new test...");
}