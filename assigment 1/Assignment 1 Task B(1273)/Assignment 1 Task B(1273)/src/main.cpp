
// --- Task B: Button Press Detection ---

// Name:Shahzaman Dhillon
// Reg. No: 23-NTU-CS-1273
// Description: Short press toggles LED, long press (>1.5s) plays buzzer tone


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Pin Configuration ---
#define BUTTON_PIN 33   // Push button pin
#define LED_PIN 18        // LED pin
#define BUZZER_PIN 16     // Buzzer pin

// --- Variables ---
unsigned long pressStartTime = 0;
bool buttonPressed = false;
bool ledState = false;
const unsigned long LONG_PRESS_TIME = 1500;  // 1.5 seconds threshold

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Active LOW button
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Task B: Button Test");
  display.display();
  delay(1500);
  display.clearDisplay();
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Detect button press start
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    pressStartTime = millis();
  }

  // Detect button release
  if (buttonState == HIGH && buttonPressed) {
    unsigned long pressDuration = millis() - pressStartTime;
    buttonPressed = false;

    if (pressDuration < LONG_PRESS_TIME) {
      // ---- Short Press Action ----
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);

      // Display event
      display.clearDisplay();
      display.setCursor(10, 20);
      display.println("Short Press:");
      display.setCursor(10, 35);
      display.print("LED ");
      display.print(ledState ? "ON" : "OFF");
      display.display();
    } else {
      // ---- Long Press Action ----
      tone(BUZZER_PIN, 1000, 500); // 1000Hz tone for 0.5s

      display.clearDisplay();
      display.setCursor(10, 25);
      display.println("Long Press:");
      display.setCursor(10, 40);
      display.println("Buzzer Sound!");
      display.display();
    }
  }
}
