#ifndef CAMERAINTERRUPT_H
#define CAMERAINTERRUPT_H

#include "InterruptPin.h"

class CameraInterrupt {
public:
    CameraInterrupt(int pin, InterruptPin::Mode mode, bool reEntryAllowed = false);

    void enable();
    void disable();

    static void cameraISR();

private:
    InterruptPin interruptPin;
};

#endif // CAMERAINTERRUPT_H
