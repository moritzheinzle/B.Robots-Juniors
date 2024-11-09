#include "InterruptPin.h"

bool InterruptPin::_isrRunning = false;
bool InterruptPin::_allowReentry = false;
int InterruptPin::_edge = RISING;
void (*InterruptPin::_isr)() = nullptr;

InterruptPin::InterruptPin(int pin, void (*isr)(), bool allowReentry, int edge) {
    _pin = pin;
    _isr = isr;
    _allowReentry = allowReentry;
    _edge = edge;
}

void InterruptPin::begin() {
    pinMode(_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(_pin), InterruptPin::interruptHandler, _edge);
}

void InterruptPin::interruptHandler() {
    if (_isrRunning && !_allowReentry) {
        return;
    }

    _isrRunning = true;
    InterruptPin::_isr();  // Auf die statische ISR-Funktion zugreifen
    _isrRunning = false;
}
