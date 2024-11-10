#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt cameraInterrupt(2, RISING, 1000);  

void userDefinedISR() {
    for (int i = 0; i < 500; i++) {
        Serial.println(i);
    }
}

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();
    cameraInterrupt.setISRHandler(userDefinedISR); 
}

void loop() {
    Serial.println("Looping...");
    delay(1000);
}
