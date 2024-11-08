#include <Arduino.h>
#include <CameraInterrupt.h>

CameraInterrupt cameraInterrupt;

void setup() {
    cameraInterrupt.begin();  // Library initialisieren
}

void loop() {
    // Die Logik ist vollständig in der Interrupt-Handler-Methode untergebracht
    // Hauptloop bleibt leer, da der Interrupt die Ausgabe übernimmt
}
