#include <Arduino.h>
#include "CameraInterrupt.h"

CameraInterrupt cameraInterrupt(2, RISING, 1000);  

void CameraISR() {
    /*
    Check if detection is possible
    Send signal to camera if detection is possible
    Camera does verification
    If verification is successful, camera will send drive commands to arduino
       
    */
}

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();
    cameraInterrupt.setISRHandler(CameraISR); 
}

void loop() {
    for (int i = 0; i < 500; i++) {
        Serial.println(i);
    }
}
