// RTS SoSe 2025
// Zakaria Boujana
// Pulse-Width-Modulation
const int potPin = A1;        
const int pwmPin = 9;         
const int digitalReadPin = 2; 

void setup() {
  Serial.begin(2000000);      
  pinMode(pwmPin, OUTPUT);
  pinMode(digitalReadPin, INPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  
  analogWrite(pwmPin, pwmValue);
  
  int digitalValue = digitalRead(digitalReadPin);
  
  // Output to Serial Plotter
  Serial.println(digitalValue, DEC);
  
  // Very short or no delay for high-frequency sampling
  delayMicroseconds(50);
}

// HOW TO VIEW THE PWM SIGNAL:
// 1. Upload this sketch to your Arduino
// 2. In Arduino IDE: Tools -> Serial Plotter
// 3. Set baud rate to 2000000 (bottom right corner)
// 4. Turn the potentiometer to see the PWM waveform change
// 5. The graph shows HIGH (1) and LOW (0) states of the PWM signal
