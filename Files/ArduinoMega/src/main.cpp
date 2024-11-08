#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt interruptHandler(2);

void setup() {
  Serial.begin(9600);
  interruptHandler.begin();
}

void loop() {
}