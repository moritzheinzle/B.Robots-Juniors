#ifndef CAMERA_INTERRUPT_H
#define CAMERA_INTERRUPT_H

#include "InterruptPin.h"
class CameraInterrupt {
public:
    CameraInterrupt(int pin, InterruptMode mode = InterruptMode::INT_RISING, bool reEntryAllowed = false);
    void enable();
    void disable();

private:
    static void cameraISR();
    InterruptPin interruptPin;
};

#endif // CAMERA_INTERRUPT_H
