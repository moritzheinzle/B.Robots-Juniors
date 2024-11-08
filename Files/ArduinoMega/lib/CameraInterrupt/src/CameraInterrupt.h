#ifndef CAMERAINTERRUPT_H
#define CAMERAINTERRUPT_H

class CameraInterrupt {
  public:
    CameraInterrupt(int pin);
    void begin();
    static void interruptHandler();  // Statische Methode für den Interrupt-Handler

  private:
    int _pin;
};

#endif
