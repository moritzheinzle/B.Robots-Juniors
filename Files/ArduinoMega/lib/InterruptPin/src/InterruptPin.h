#ifndef INTERRUPTPIN_H
#define INTERRUPTPIN_H

#include <Arduino.h>

class InterruptPin {
public:
    static volatile bool isISRRunning;  // Declare as volatile and static

    typedef enum {
        INT_RISING = RISING,
        INT_FALLING = FALLING,
        INT_CHANGE = CHANGE
    } Mode;

    InterruptPin(int pin, void (*ISR)(), Mode mode, bool reEntryAllowed = false);

    void enable();
    void disable();

    static void handleInterrupt();

    static void setUserISR(void (*ISR)());
    static void setCustomISR(void (*ISR)());
    static void allowReEntry(bool allowed);

private:
    static bool interruptIsInISR();

    int pin;
    Mode mode;

    static void (*userISR)();
    static void (*customISR)();
    static bool reEntryAllowed;
};

#endif // INTERRUPTPIN_H
