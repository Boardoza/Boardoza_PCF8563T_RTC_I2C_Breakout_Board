#include <Wire.h>
#include "PCF8563.h"

PCF8563 rtc;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for the serial port open

  if (!rtc.begin()) {
    Serial.println("PCF8563 RTC not found!");
    while (1);
  }
  
  // Check if the RTC time is valid
  if (!rtc.isTimeValid()) {
    // If the time is invalid, set the time for the first time or if the RTC is reset.
    if (rtc.setTime(2025, 4, 4, 08, 06, 05)) {
      Serial.println("The time was successfully set.");
    } else {
      Serial.println("Time could not be set!");
    }
  } else {
    Serial.println("RTC time valid, not readjusting.");
  }
}

void loop() {
  DateTime now;
  if (rtc.getTime(now)) {
    Serial.print("Time: ");
    Serial.print(now.year); Serial.print("-");
    Serial.print(now.month); Serial.print("-");
    Serial.print(now.day); Serial.print(" ");
    Serial.print(now.hour); Serial.print(":");
    Serial.print(now.minute); Serial.print(":");
    Serial.println(now.second);
  } else {
    Serial.println("Time could not be read!");
  }
  delay(1000);
}
