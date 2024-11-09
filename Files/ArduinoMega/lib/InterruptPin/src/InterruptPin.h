#ifndef INTERRUPT_PIN_H
#define INTERRUPT_PIN_H

class InterruptPin {
public:
    // Umbenennung von RISING, FALLING und CHANGE
    enum class Mode { INT_RISING, INT_FALLING, INT_CHANGE };

    InterruptPin(int pin, void (*ISR)(), Mode mode, bool reEntryAllowed);
    void enable();
    void disable();
    static void handleInterrupt();
    static void setUserISR(void (*ISR)());
    static void setCustomISR(void (*ISR)());
    static void allowReEntry(bool allowed);
    static bool interruptIsInISR();

private:
    static volatile bool isISRRunning;
    static void (*userISR)();
    static void (*customISR)();
    static bool reEntryAllowed;
    int pin;
    Mode mode;
};

#endif
