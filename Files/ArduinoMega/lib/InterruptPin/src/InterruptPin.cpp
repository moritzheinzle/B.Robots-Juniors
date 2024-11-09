#include "InterruptPin.h"

volatile bool InterruptPin::isISRRunning = false;  // Define static volatile variable

void (*InterruptPin::userISR)() = nullptr;
void (*InterruptPin::customISR)() = nullptr;
bool InterruptPin::reEntryAllowed = false;

InterruptPin::InterruptPin(int pin, void (*ISR)(), Mode mode, bool reEntryAllowed)
    : pin(pin), mode(mode) {
    setCustomISR(ISR);
    allowReEntry(reEntryAllowed);
}

void InterruptPin::enable() {
    attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt, mode);
}

void InterruptPin::disable() {
    detachInterrupt(digitalPinToInterrupt(pin));
}

void InterruptPin::handleInterrupt() {
    cli(); 
    if (isISRRunning) {
        return;
    }

    // Disable interrupts globally to prevent re-entry during ISR
    cli(); // Disable global interrupts

    isISRRunning = true;
    
    if (customISR) {
        if (reEntryAllowed || !interruptIsInISR()) {
            customISR();
        }
    }
    else if (userISR) {
        if (reEntryAllowed || !interruptIsInISR()) {
            userISR();
        }
    }

    isISRRunning = false;

    // Re-enable global interrupts after ISR is done
    sei(); // Enable global interrupts
}


bool InterruptPin::interruptIsInISR() {
    return isISRRunning;
}

void InterruptPin::setUserISR(void (*ISR)()) {
    userISR = ISR;
}

void InterruptPin::setCustomISR(void (*ISR)()) {
    customISR = ISR;
}

void InterruptPin::allowReEntry(bool allowed) {
    reEntryAllowed = allowed;
}
