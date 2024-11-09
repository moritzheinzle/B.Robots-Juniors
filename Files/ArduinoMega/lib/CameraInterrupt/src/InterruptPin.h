#ifndef INTERRUPTPIN_H
#define INTERRUPTPIN_H

#include <Arduino.h>
class InterruptPin {
public:
    InterruptPin(int pin, void (*handler)());
    void begin();
    void resetInterrupt();
private:
    int _pin;                            
    void (*_handler)();                 
    static void interruptWrapper();      
    static InterruptPin* instance;        
};

#endif
