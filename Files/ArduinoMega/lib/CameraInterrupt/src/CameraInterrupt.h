#ifndef CAMERA_INTERRUPT_H
#define CAMERA_INTERRUPT_H

#include "InterruptPin.h"

// CameraInterrupt class to manage the camera interrupt
class CameraInterrupt {
public:
    // Constructor that takes the pin, mode (int), and re-entry permission
    CameraInterrupt(int pin, int mode = RISING, bool reEntryAllowed = false);

    // Method to enable the interrupt
    void enable();

    // Method to disable the interrupt
    void disable();

private:
    // Custom ISR for handling the interrupt
    static void cameraISR();

    // InterruptPin instance for managing the pin and interrupts
    InterruptPin interruptPin;
};

#endif // CAMERA_INTERRUPT_H
