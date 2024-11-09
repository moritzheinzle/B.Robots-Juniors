#include "InterruptPin.h"

volatile bool InterruptPin::isISRRunning = false;
void (*InterruptPin::userISR)() = nullptr;
void (*InterruptPin::customISR)() = nullptr;
bool InterruptPin::reEntryAllowed = false;

void InterruptPin::handleInterrupt() {
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

