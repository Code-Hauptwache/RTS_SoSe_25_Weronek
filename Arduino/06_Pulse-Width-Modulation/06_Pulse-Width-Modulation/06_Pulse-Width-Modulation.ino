// RTS SoSe 2025
// Zakaria Boujana
// Pulse-Width-Modulation
const int potPin = A1;        // Potentiometer on analog pin A1
const int pwmPin = 9;         // PWM output pin
const int digitalReadPin = 2; // Digital input to read PWM signal

void setup() {
  Serial.begin(2000000);      // High baud rate for fast sampling
  pinMode(pwmPin, OUTPUT);    // Set PWM pin as output
  pinMode(digitalReadPin, INPUT); // Set digital pin as input
}

void loop() {
  // Read potentiometer (0-1023)
  int potValue = analogRead(potPin);
  
  // Map to PWM range (0-255)
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  
  // Write PWM value
  analogWrite(pwmPin, pwmValue);
  
  // Read the PWM signal on digital input
  int digitalValue = digitalRead(digitalReadPin);
  
  // Output to Serial Plotter
  Serial.println(digitalValue, DEC);
  
  // Very short or no delay for high-frequency sampling
  delayMicroseconds(50); // 50 microseconds delay
}

// HOW TO VIEW THE PWM SIGNAL:
// 1. Upload this sketch to your Arduino
// 2. In Arduino IDE: Tools -> Serial Plotter
// 3. Set baud rate to 2000000 (bottom right corner)
// 4. Turn the potentiometer to see the PWM waveform change
// 5. The graph shows HIGH (1) and LOW (0) states of the PWM signal
