#include "CameraInterrupt.h"

CameraInterrupt* CameraInterrupt::instance = nullptr; 

CameraInterrupt::CameraInterrupt(uint8_t interruptPin, int mode, unsigned long debounceDelay)
    : _interruptPin(interruptPin), _mode(mode), _debounceDelay(debounceDelay), _lastTriggerTime(0), _isrHandled(false), _isrHandler(nullptr) {
    instance = this; 
}

void CameraInterrupt::begin() {
    pinMode(_interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(_interruptPin), handleISR, _mode);
}

void CameraInterrupt::end() {
    detachInterrupt(digitalPinToInterrupt(_interruptPin));
}

void CameraInterrupt::setISRHandler(void (*handler)()) {
    _isrHandler = handler;
}

void CameraInterrupt::resetInterrupt() {

    unsigned long currentMillis = millis();

    if (currentMillis - _lastTriggerTime >= _debounceDelay) {
        _lastTriggerTime = currentMillis;
        _isrHandled = false;
        attachInterrupt(digitalPinToInterrupt(_interruptPin), handleISR, _mode); 
    }
}

void CameraInterrupt::handleISR() {

    if (!instance) return;

    noInterrupts(); 

    if (instance->_isrHandled) {
        interrupts();  
        return;  
    }

    instance->_isrHandled = true; 

    if (instance->_isrHandler) {
        instance->_isrHandler();
    }

    interrupts();
    instance->resetInterrupt();
}

