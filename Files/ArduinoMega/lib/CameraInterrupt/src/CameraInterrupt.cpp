#include "CameraInterrupt.h"
#include <Arduino.h>

void CameraInterrupt::cameraISR() {
    for (int i = 1; i <= 1000; i++) {
    Serial.println(i);  // Gibt die Zahl aus
}
}

CameraInterrupt::CameraInterrupt(int pin, InterruptPin::Mode mode, bool reEntryAllowed)
    : interruptPin(pin, cameraISR, mode, reEntryAllowed) {
}

void CameraInterrupt::enable() {
    interruptPin.enable();
}

void CameraInterrupt::disable() {
    interruptPin.disable();
}
