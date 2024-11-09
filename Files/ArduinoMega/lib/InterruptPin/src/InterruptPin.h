#ifndef INTERRUPTPIN_H
#define INTERRUPTPIN_H

#include <Arduino.h>

class InterruptPin {
public:
    InterruptPin(int pin, void (*isr)(), bool allowReentry = false, int edge = RISING);
    void begin();
    static void interruptHandler();

private:
    int _pin;
    static void (*_isr)();  // Funktion als statische Variable speichern
    static bool _isrRunning;
    static bool _allowReentry;
    static int _edge;
};

#endif
