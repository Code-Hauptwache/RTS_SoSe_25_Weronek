// RTS SoSe 2025
// Zakaria Boujana
// Approach Lights 2

// Define LED pins
const int LED_PINS[] = {5, 6, 7, 8, 9, 10, 11, 12};
const int MAX_LEDS = 8;

// Define control pins
const int RUN_BUTTON_PIN = 2; // Button for run mode
const int CONFIG_BUTTON_PIN = 3;  // Button for config mode
const int POT_PIN = A0; // Potentiometer Input

// Mode control
enum Mode {RUN, CONFIG};
Mode currentMode = CONFIG;  // Start in CONFIG Mode
Mode lastMode;

volatile unsigned long lastButtonPress = 0;
int potValue;
int sequenceLength;

void setup() {
  // Initialize Serial
  Serial.begin(9600);
  Serial.println("System started - Config mode");

  for (int i = 0; i < MAX_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH); // All LEDs off (active low)
  }

  pinMode(RUN_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RUN_BUTTON_PIN), runButtonISR, FALLING);
  
  pinMode(CONFIG_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CONFIG_BUTTON_PIN), configButtonISR, FALLING);
}

void loop () {
  if (currentMode == RUN) {
    runMode();
  }
  else {
    configMode();
  }
}

void runMode() {
  
  // Only read pot when first entering RUN mode
  if (lastMode != currentMode) {    
    // Calculate sequence length from locked value
    sequenceLength = map(potValue, 0, 1023, 1, MAX_LEDS);
    sequenceLength = max(1, sequenceLength);
    
    lastMode = currentMode;
    
    // Reset all LEDs when switching to run mode
    for (int i = 0; i < MAX_LEDS; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
  }
  
  // Calculate timing to maintain 2Hz frequency
  int totalOnTime = sequenceLength * 2;
  int remainingTime = 500 - totalOnTime;
  int stepDuration = remainingTime / (sequenceLength + 1);
  
  // Run sequence
  for (int i = 0; i < sequenceLength; i++) {
    if (currentMode == CONFIG) break;
      
    digitalWrite(LED_PINS[i], LOW);
    for (int j = 0; j < 2; j++) {
        if (currentMode == CONFIG) break;
        delay(1);
    }
    digitalWrite(LED_PINS[i], HIGH);
    for (int j = 0; j < stepDuration; j++) {
        if (currentMode == CONFIG) break;
        delay(1);
    }
  }
  
  if (currentMode == RUN) {
    for (int j = 0; j < stepDuration; j++) {
        if (currentMode == CONFIG) break;
        delay(1);
    }
    
    // Print potentiometer value after sequence
    Serial.print("Potentiometer value: ");
    Serial.print(potValue);
    Serial.print(", Sequence length: ");
    Serial.println(sequenceLength);
  }
}

void configMode() {
  // Read current pot value (live updates)
  potValue = analogRead(POT_PIN);
  sequenceLength = map(potValue, 0, 1023, 1, MAX_LEDS);
  sequenceLength = max(1, sequenceLength);

  // Update LED display
  for (int i = 0; i < MAX_LEDS; i++) {
    if (i < sequenceLength) {
      digitalWrite(LED_PINS[i], LOW);
    } else {
      digitalWrite(LED_PINS[i], HIGH);
    }
  }
  
  // Small delay to prevent flickering
  delay(50);
}


void runButtonISR() {
  unsigned long currentTime = millis();
  
  // Debounce - only accept button press if 200ms passed
  if (currentTime - lastButtonPress > 200) {
    lastMode = currentMode;
    currentMode = RUN;
    lastButtonPress = currentTime;
  }
}

void configButtonISR() {
  unsigned long currentTime = millis();
  
  // Debounce - only accept button press if 200ms passed
  if (currentTime - lastButtonPress > 200) {
    lastMode = currentMode;
    currentMode = CONFIG;
    lastButtonPress = currentTime;
  }
}