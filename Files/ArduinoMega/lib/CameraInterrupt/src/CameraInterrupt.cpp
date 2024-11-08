#include "CameraInterrupt.h"
#include <Arduino.h>

CameraInterrupt::CameraInterrupt(int pin) {
  _pin = pin;
}

void CameraInterrupt::begin() {
  pinMode(_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_pin), CameraInterrupt::interruptHandler, CHANGE);  // Statische Methode verwenden
}

void CameraInterrupt::interruptHandler() {
  Serial.println("Interrupt ausgelöst!");  // Die eigentliche Interrupt-Logik
}
