#ifndef TALLYCOUNTER_H
#define TALLYCOUNTER_H

#include <Arduino.h>
#include "constants.h"
#include "Button.h"
#include "Buzzer.h"
#include <EEPROM.h>

typedef enum
{
    COUNTING,
    SETTING_THRESHOLD,
    ALARM
} state_t;

class TallyCounter
{
private:
    uint16_t _number{0}; // number to be displayed
    uint16_t _threshold{DEFAULT_THD_VALUE};    // threshold
    byte _data{B00000000};   // raw data to manipulate shift. register
    state_t _state{COUNTING};
    bool _boot{false};  // indicates if data has been written to eeprom before or not

    Button IncButton;
    Button DecButton;
    Button ThdButton;
    Buzzer Buzzer;

public:

    // ctor with buttons
    TallyCounter(uint8_t inc_pin, uint8_t dec_pin, uint8_t thd_pin, uint8_t buzzer_pin);
    
    // enables all pins on setup
    void enable_pins();

    // reads buttons, main state transition logic
    void read_buttons();

    // feeds number into shift register (simplifies code)
    void update_shift_reg(uint8_t num);

    // displays number on 7-segs (either number or threshold depending on state)
    void display_number();

    // plays alarm
    void play_alarm();

    // updates EEPROM
    void update_EEPROM();

    // loads number and threshold from EEPROM on boot if present
    void load_EEPROM();

    // get current state
    state_t get_state();
};

#endif