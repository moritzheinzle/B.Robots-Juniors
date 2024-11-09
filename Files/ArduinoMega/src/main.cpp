#include <Arduino.h>
#include <CameraInterrupt.h>

CameraInterrupt cameraInterrupt(2, InterruptPin::Mode::FALLING, false);

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();
}

void loop() {
    delay(1000);
    Serial.println("Camera interrupt system active!");
}
