#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt cameraInterrupt(2, RISING, true);

void setup() {
    Serial.begin(9600);
    cameraInterrupt.enable();
}

void loop() {
    delay(1000);
}
