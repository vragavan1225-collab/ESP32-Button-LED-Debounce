const int BUTTON_PIN = 4; // Push button connected to GPIO 4
const int LED_PIN = 5;    // External LED connected to GPIO 5

// State Variables
int ledState = LOW;         // Current state of the LED
int buttonState = HIGH;     // Current reading from the button pin
int lastButtonState = HIGH; // Previous reading from the button pin

// Debounce Variables
unsigned long lastDebounceTime = 0;  
const unsigned long debounceDelay = 50; // 50ms debounce threshold

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Internal pull-up (Pressed = LOW)
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // Reset debounce timer if state changed (noise or press)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // If signal remained stable longer than debounce threshold
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Toggle LED when button is pressed (HIGH to LOW)
      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }

  lastButtonState = reading;
}
