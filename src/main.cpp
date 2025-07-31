#include <Arduino.h>

void setup() {
  // Initialize serial communication at 115200 bits per second.
  // This should be the VERY first thing to run.
  Serial.begin(115200);

  // Add a small delay to ensure the serial monitor can connect in time.
  delay(2500); 

  // Use a loop to repeatedly print, making it more likely to be seen
  // even if the board resets quickly.
  for (int i = 0; i < 5; i++) {
    Serial.println("--- Copilot Debug: setup() has started. Serial is OK. ---");
    delay(100);
  }
}

void loop() {
  // The loop is kept empty to prevent other code from running.
  Serial.println("--- Copilot Debug: loop() is running. ---");
  delay(5000);
}