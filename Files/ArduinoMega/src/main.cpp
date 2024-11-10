#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt cameraInterrupt(2, RISING, 1000);  // 500ms debounce delay

void userDefinedISR() {
    for (int i = 0; i < 500; i++) {
        Serial.println(i);
    }
}

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();
    cameraInterrupt.setISRHandler(userDefinedISR);  // Set the user-defined ISR
}

void loop() {
    Serial.println("Looping...");
    delay(1000);
}
