#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "constants.h"
#include "buzzer_defines.h"

class Buzzer
{
private:
    uint8_t _pin_buzzer;
    uint8_t _pin_red_led;
    uint8_t _pin_green_led;
    uint8_t counter{0};

    // internal functions, only to be used within class
    void beep(const sound_t& sound);

public:
    // ctor
    Buzzer(uint8_t pin_buzzer, uint8_t pin_red_led, uint8_t pin_green_led);

    // play alarm sound
    void alarm();

    // play notification sound
    void notification();

    // disable playing
    void disable();
};

#endif