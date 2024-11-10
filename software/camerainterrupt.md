# CameraInterrupt&#x20;

## Overview

The `CameraInterrupt` library allows you to handle external interrupts on an Arduino board with proper debouncing and custom interrupt service routines (ISRs). It ensures that an interrupt is triggered only once during the debounce period, even if the signal on the pin fluctuates.

## Features

* **Interrupt Debouncing**: Prevents multiple triggers within a short time frame.
* **Custom ISR**: Allows you to define your custom interrupt handler.
* **Non-blocking**: Does not block the main loop while the interrupt is triggered.

### Constructor

```cpp
CameraInterrupt(uint8_t interruptPin, int mode, unsigned long debounceDelay = 500);
```

* **`interruptPin`**: The pin to attach the interrupt to.
* **`mode`**: Triggering mode for the interrupt (e.g., `RISING`, `FALLING`, `CHANGE`).
* **`debounceDelay`**: Time in milliseconds to wait before allowing another interrupt. Default is 500ms.

### Methods

#### `begin()`

Starts listening for interrupts on the specified pin.

```cpp
cameraInterrupt.begin();
```

#### `end()`

Stops listening for interrupts on the specified pin.

```cpp
cameraInterrupt.end();
```

#### `setISRHandler(void (*handler)())`

Sets the custom ISR handler function.

```cpp
cameraInterrupt.setISRHandler(userDefinedISR);
```

#### `resetInterrupt()`

Handles the debounce and re-enables the interrupt if enough time has passed.

#### `handleISR()`

Handles the interrupt and ensures the ISR is called only once per event.

### Example

```cpp
#include "CameraInterrupt.h"

// Create the CameraInterrupt object on pin 2 with a debounce of 500ms
CameraInterrupt cameraInterrupt(2, RISING, 500);

// Custom ISR to handle the interrupt
void userDefinedISR() {
    Serial.println("Custom ISR Triggered!");
}

void setup() {
    Serial.begin(9600);
    cameraInterrupt.begin();               // Initialize the interrupt
    cameraInterrupt.setISRHandler(userDefinedISR);  // Set the custom ISR function
}

void loop() {
    // The main loop does nothing in this example, the interrupt is handled by the ISR
}
```

***

## License

This library is open-source and available for free under the MIT License.
