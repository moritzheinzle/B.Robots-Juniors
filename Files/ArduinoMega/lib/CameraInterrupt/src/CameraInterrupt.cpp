#include "CameraInterrupt.h"

CameraInterrupt::CameraInterrupt(int pin, InterruptPin::Mode mode, bool reEntryAllowed)
    : interruptPin(pin, handleCameraISR, mode, reEntryAllowed) {}

e
void CameraInterrupt::begin() {
    interruptPin.enable();
}

void CameraInterrupt::handleCameraISR() {
    
}
