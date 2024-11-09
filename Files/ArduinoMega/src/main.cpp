#include <CameraInterrupt.h>

CameraInterrupt cameraInterrupt(2);  // Beispiel: Pin 2 für den Interrupt

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();  // Startet den Interrupt auf Pin 2
}

void loop() {
    // Deine Hauptlogik hier
}
