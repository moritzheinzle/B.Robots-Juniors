#ifndef CAMERA_INTERRUPT_H
#define CAMERA_INTERRUPT_H

#include "InterruptPin.h"

class CameraInterrupt {
public:
    CameraInterrupt(int pin, InterruptPin::Mode mode, bool reEntryAllowed);
    void begin();
    int getInterruptCount() const;

private:
    InterruptPin interruptPin;
    static void handleCameraISR();
    static volatile int interruptCount;
};

#endif
