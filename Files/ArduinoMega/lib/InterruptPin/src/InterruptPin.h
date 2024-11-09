#ifndef INTERRUPT_PIN_H
#define INTERRUPT_PIN_H

#include <Arduino.h>

class InterruptPin {
public:
    static bool isISRRunning;
    static void (*userISR)();
    static void (*customISR)();
    static bool reEntryAllowed;

    InterruptPin(int pin, void (*ISR)(), int mode, bool reEntryAllowed = false);
    void enable();
    void disable();

    static void handleInterrupt();
    static bool interruptIsInISR();
    void setUserISR(void (*ISR)());
    void setCustomISR(void (*ISR)());
    void allowReEntry(bool allowed);

private:
    int pin;
    int mode;
};

#endif // INTERRUPT_PIN_H
