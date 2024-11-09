#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt cameraInterrupt(2, InterruptPin::INT_RISING, true);  // Correct Mode type

void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP);  // Set pin 2 as input with pull-up resistor
    cameraInterrupt.enable();  // Enable the interrupt
}

void loop() {
    // Your main loop logic
    Serial.println("Looping...");
    delay(1000);
}
