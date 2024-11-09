#include <Arduino.h>
#include <CameraInterrupt.h>

CameraInterrupt cameraInterrupt(2, InterruptPin::Mode::INT_FALLING, false);

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();
}

void loop() {
    // Die serielle Ausgabe wird im ISR-Handler behandelt
}
