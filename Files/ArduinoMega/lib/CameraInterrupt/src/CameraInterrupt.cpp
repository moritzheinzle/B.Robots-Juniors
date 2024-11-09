#include "CameraInterrupt.h"

bool CameraInterrupt::_isrRunning = false;

CameraInterrupt::CameraInterrupt(int pin) {
    _pin = pin;
}

void CameraInterrupt::begin() {
    InterruptPin interruptPin(_pin, CameraInterrupt::interruptHandler, false, RISING); 
    interruptPin.begin();
}

void CameraInterrupt::interruptHandler() {
    if (_isrRunning) {
        return;
    }
    
    _isrRunning = true;
    handleISR();
    _isrRunning = false;
}

void CameraInterrupt::handleISR() {
    // Hier kommt die Logik der ISR, z. B. die Verarbeitung eines Kamerasignals
    Serial.println("Interrupt in CameraInterrupt ausgelöst!");
}
