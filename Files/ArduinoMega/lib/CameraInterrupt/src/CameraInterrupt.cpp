#include "CameraInterrupt.h"
#include <Arduino.h>  // Ensure this is included for Serial

// Static camera ISR function
void CameraInterrupt::cameraISR() {
    // Custom ISR code for handling camera interrupt
    Serial.println("Camera interrupt triggered!");

    // You can add specific camera interrupt logic here
}

// Constructor: Initializes the CameraInterrupt with a pin and mode
CameraInterrupt::CameraInterrupt(int pin, int mode, bool reEntryAllowed)
    : interruptPin(pin, cameraISR, mode, reEntryAllowed) {
    // The constructor automatically sets the camera ISR for the pin
}

// Enable the camera interrupt (using the InterruptPin instance)
void CameraInterrupt::enable() {
    interruptPin.enable();
}

// Disable the camera interrupt
void CameraInterrupt::disable() {
    interruptPin.disable();
}
