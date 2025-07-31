#include <Arduino.h>

void setup() {
  // CRITICAL: This should be the VERY first line to ensure serial output
  Serial.begin(115200);
  
  // Wait for serial monitor to connect (critical for USB CDC)
  delay(2000);
  
  // Multiple boot indicators for maximum visibility
  Serial.println("=================================================");
  Serial.println("ESP32-S3 BOOT SEQUENCE STARTED");
  Serial.println("=================================================");
  
  // System information
  Serial.print("ESP32 Chip: ");
  Serial.println(ESP.getChipModel());
  Serial.print("CPU Frequency: ");  
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
  
  // PSRAM check
  if (ESP.getPsramSize() > 0) {
    Serial.print("PSRAM Size: ");
    Serial.print(ESP.getPsramSize());
    Serial.println(" bytes");
    Serial.print("Free PSRAM: ");
    Serial.print(ESP.getFreePsram());
    Serial.println(" bytes");
  } else {
    Serial.println("PSRAM: Not available or not enabled");
  }
  
  // Boot milestone indicators
  for (int i = 1; i <= 5; i++) {
    Serial.print("BOOT MILESTONE ");
    Serial.print(i);
    Serial.println(" - System Running OK");
    delay(200);
  }
  
  Serial.println("=================================================");
  Serial.println("SETUP COMPLETE - Entering main loop");
  Serial.println("=================================================");
}

void loop() {
  static unsigned long lastPrint = 0;
  static int loopCounter = 0;
  
  unsigned long currentTime = millis();
  
  // Print every 5 seconds
  if (currentTime - lastPrint >= 5000) {
    loopCounter++;
    Serial.print("LOOP ");
    Serial.print(loopCounter);
    Serial.print(" - Runtime: ");
    Serial.print(currentTime / 1000);
    Serial.print("s - Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    
    lastPrint = currentTime;
  }
  
  // Small delay to prevent watchdog issues
  delay(10);
}