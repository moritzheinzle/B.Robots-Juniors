#ifndef CAMERAINTERRUPT_H
#define CAMERAINTERRUPT_H

#include <Arduino.h>
#include <InterruptPin.h>

class CameraInterrupt {
public:
    CameraInterrupt(int pin);
    void begin();
    static void interruptHandler();

private:
    int _pin;
    static bool _isrRunning;
    static void handleISR();
};

#endif
