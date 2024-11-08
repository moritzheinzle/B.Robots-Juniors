#include "CameraInterrupt.h"

// Konstruktor
CameraInterrupt::CameraInterrupt() {}

// Initialisierung der Library
void CameraInterrupt::begin() {
    // Setup des Interrupts auf Pin 2 (PWM Pin 2 auf Arduino Mega)
    attachInterrupt(digitalPinToInterrupt(2), [this]() { this->handleInterrupt(); }, RISING);
    Serial.begin(9600);  // Serielle Kommunikation starten
}

// Interrupt-Handler
void CameraInterrupt::handleInterrupt() {
    // Gibt die Nachricht "Interrupt" auf dem seriellen Terminal aus
    Serial.println(interruptMessage);  
}
