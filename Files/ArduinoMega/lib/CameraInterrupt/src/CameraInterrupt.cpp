#include "CameraInterrupt.h"

CameraInterrupt* CameraInterrupt::instance = nullptr;  // Initialize static pointer

CameraInterrupt::CameraInterrupt(uint8_t interruptPin, int mode, unsigned long debounceDelay)
    : _interruptPin(interruptPin), _mode(mode), _debounceDelay(debounceDelay), _lastTriggerTime(0), _isrHandled(false), _isrHandler(nullptr) {
    instance = this;  // Assign the instance pointer
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
        // Re-enable interrupt after debounce period
        _lastTriggerTime = currentMillis;  // Update the last trigger time
        _isrHandled = false;  // Allow new interrupt after debounce
        attachInterrupt(digitalPinToInterrupt(_interruptPin), handleISR, _mode);  // Re-enable interrupt
    }
}

void CameraInterrupt::handleISR() {
    if (!instance) return;  // Safety check if instance is not initialized

    // Ensure that interrupt is disabled during the ISR execution
    noInterrupts();  // Disable interrupts to prevent re-entry during ISR

    // Prevent interrupt from being handled multiple times until reset
    if (instance->_isrHandled) {
        interrupts();  // Re-enable interrupts before returning
        return;  // Skip ISR if it's already been handled
    }
    instance->_isrHandled = true;  // Mark ISR as handled

    // Call the user-defined ISR handler if set
    if (instance->_isrHandler) {
        instance->_isrHandler();
    }

    interrupts();  // Re-enable interrupts after ISR execution

    // Handle the debounce and reset the interrupt
    instance->resetInterrupt();
}

