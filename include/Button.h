#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "constants.h"

class Button
{
private:
    uint8_t _pin;
    uint16_t _long_press_time{LONG_PRESS_INTERVAL};
    bool _state{HIGH};
    bool _short_press_detected{};
    bool _long_press_detected{};

public:
    // Constructor
    Button(uint8_t pin, uint16_t long_press_time);

    // Read button state
    void read();

    // Getters
    bool isShortPressDetected();
    bool isLongPressDetected();
};

#endif