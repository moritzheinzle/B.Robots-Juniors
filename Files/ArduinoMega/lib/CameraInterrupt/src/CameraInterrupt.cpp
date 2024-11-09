#include "CameraInterrupt.h"

void CameraInterrupt::cameraISR() {
    Serial.println("Camera interrupt triggered!");
}
CameraInterrupt::CameraInterrupt(int pin, InterruptMode mode, bool reEntryAllowed)
    : interruptPin(pin, cameraISR, mode, reEntryAllowed) {
}
void CameraInterrupt::enable() {
    interruptPin.enable();
}
void CameraInterrupt::disable() {
    interruptPin.disable();
}
