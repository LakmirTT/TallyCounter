#include "Buzzer.h"
#include "buzzer_defines.h"
#include "sounds.h"

// ctor
Buzzer::Buzzer(uint8_t pin_buzzer, uint8_t pin_red_led, uint8_t pin_green_led)
{
    this->_pin_buzzer = pin_buzzer;
    this->_pin_red_led = pin_red_led;
    this->_pin_green_led = pin_green_led;
    pinMode(pin_buzzer, OUTPUT);
}

// play alarm sound
void Buzzer::alarm()
{
    
    static int i = 0;
    beep(array_alarm_sound[i]);
    i = (++i) % (sizeof(array_alarm_sound) / sizeof(sound_t) + 1);
}

// play notification sound
void Buzzer::notification()
{
  // Iterate through the melody array and play each note
  for (int i = 0; i < sizeof(array_notification_sound) / sizeof(sound_t); i++)
  {
    digitalWrite(PIN_LED_GREEN, HIGH);
    beep(array_notification_sound[i]);
    delay(50); // Delay between each note
    digitalWrite(PIN_LED_GREEN, LOW);
  }
}

// disable playing
void Buzzer::disable()
{
    noTone(_pin_buzzer);
    digitalWrite(_pin_red_led, LOW);
    digitalWrite(_pin_green_led, LOW);
}

// internal functions, only to be used within class public methods
void Buzzer::beep(const sound_t& sound)
{
    // Play tone on buzzerPin
    tone(_pin_buzzer, sound.note, sound.duration);

    // Play different LED depending on value of 'counter'
    if (counter % 2 == 0)
    {
        digitalWrite(_pin_green_led, HIGH);
        delay(sound.duration);
        digitalWrite(_pin_green_led, LOW);
    }
    else
    {
        digitalWrite(_pin_red_led, HIGH);
        delay(sound.duration);
        digitalWrite(_pin_red_led, LOW);
    }

    // Stop tone on buzzerPin
    noTone(_pin_buzzer);

    delay(50);

    // Increment counter
    counter++;
}