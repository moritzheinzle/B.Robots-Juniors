#ifndef CAMERA_INTERRUPT_H
#define CAMERA_INTERRUPT_H

#include <Arduino.h>

class CameraInterrupt {
public:
    CameraInterrupt();
    void begin();
    void handleInterrupt();

private:
    const char* interruptMessage = "Interrupt";  // Nachricht, die bei jedem Interrupt ausgegeben wird
};

#endif
