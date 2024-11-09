#include "InterruptPin.h"

InterruptPin* InterruptPin::instance = nullptr;

InterruptPin::InterruptPin(int pin, void (*handler)()) : _pin(pin), _handler(handler) {
    instance = this;
}
void InterruptPin::begin() {
    pinMode(_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(_pin), InterruptPin::interruptWrapper, RISING);
}
void InterruptPin::interruptWrapper() {
    if (instance) {
        detachInterrupt(digitalPinToInterrupt(instance->_pin));
        instance->_handler();
        instance->resetInterrupt();
    }
}
void InterruptPin::resetInterrupt() {
    attachInterrupt(digitalPinToInterrupt(_pin), InterruptPin::interruptWrapper, RISING); // Aktiviert den Interrupt erneut
}
