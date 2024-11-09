#ifndef INTERRUPT_PIN_H
#define INTERRUPT_PIN_H

#include <Arduino.h>

class InterruptPin {
public:
    static volatile bool isISRRunning;
    static void (*userISR)();
    static void (*customISR)();
    static bool reEntryAllowed;

    static void handleInterrupt();
    static bool interruptIsInISR();

    static void setUserISR(void (*ISR)());
    static void setCustomISR(void (*ISR)());
    static void allowReEntry(bool allowed);
};

#endif
