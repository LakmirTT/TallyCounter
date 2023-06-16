#include "Button.h"

Button::Button(uint8_t pin, uint16_t long_press_time)
{
    _pin = pin;
    _long_press_time = long_press_time;

    // Initialize button pin
    pinMode(_pin, INPUT_PULLUP);
}

void Button::read()
{
    uint8_t new_state = digitalRead(_pin);

    // Check if button state has changed
    if (new_state != _state)
    {
        delay(WAIT);
        if (new_state == LOW)
        {
            uint32_t start_time = millis();
            bool long_press = false;
            while (digitalRead(_pin) == LOW)
            {
                if (millis() - start_time >= _long_press_time)
                {
                    long_press = true;
                    break;
                }
            }

            if (long_press)
            {
                _long_press_detected = true;
                _short_press_detected = false;
            }
            else
            {
                _long_press_detected = false;
                _short_press_detected = true;
            }
        }
        else
        {
            _long_press_detected = false;
            _short_press_detected = false;
        }

        _state = new_state;
    }
}

bool Button::isShortPressDetected()
{
    return _short_press_detected;
}

bool Button::isLongPressDetected()
{
    return _long_press_detected;
}
