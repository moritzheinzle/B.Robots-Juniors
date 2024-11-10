#ifndef CAMERA_INTERRUPT_H
#define CAMERA_INTERRUPT_H

#include <Arduino.h>

class CameraInterrupt {
public:
    CameraInterrupt(uint8_t interruptPin, int mode, unsigned long debounceDelay = 500);
    void begin();
    void end();
    void setISRHandler(void (*handler)());

private:
    uint8_t _interruptPin;
    int _mode;
    unsigned long _debounceDelay;
    unsigned long _lastTriggerTime;
    bool _isrHandled;
    static CameraInterrupt* instance; 
    void (*_isrHandler)();

    static void handleISR();  
    void resetInterrupt();  
};

#endif 