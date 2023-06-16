#include "TallyCounter.h"

// ctor with buttons
TallyCounter::TallyCounter(uint8_t inc_pin, uint8_t dec_pin, uint8_t thd_pin, uint8_t buzzer_pin) :
IncButton(inc_pin, LONG_PRESS_INTERVAL), 
DecButton(dec_pin, LONG_PRESS_INTERVAL), 
ThdButton(thd_pin, LONG_PRESS_INTERVAL),
Buzzer(buzzer_pin, PIN_LED_RED, PIN_LED_GREEN)
{}

// enables all pins on setup
void TallyCounter::enable_pins()
{
    //Serial.begin(9600);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);

    pinMode(PIN_SR_CLK, OUTPUT);
    pinMode(PIN_SR_DATA, OUTPUT);
    pinMode(PIN_SR_LATCH, OUTPUT);
}

// reads buttons, main state transition logic
void TallyCounter::read_buttons()
{
    IncButton.read();
    DecButton.read();
    ThdButton.read();
    // сheck decrement button
    if (DecButton.isShortPressDetected())
    {
        if (_state == COUNTING)
        {
            if (_number > 0 && _number - 1 >= 0) _number--;
            delay(200); // Delay to avoid rapid number changes
        }
        else if (_state == SETTING_THRESHOLD)
        {
            if (_threshold > 0 && _threshold - 1 >= 0) _threshold--;
            if (_number >= _threshold) _number = _threshold;
            delay(200); // Delay to avoid rapid changes
        }
    }
    else if (DecButton.isLongPressDetected())
    {
        if (_state == COUNTING)
        {
            if ( _number >= 10) _number = _number - 10;
            delay(200); // Delay to avoid rapid number changes
        }
        else if (_state == SETTING_THRESHOLD)
        {
            if (_threshold >= 10) _threshold = _threshold - 10;
            if (_number >= _threshold) _number = _threshold;
            delay(200); // Delay to avoid rapid changes
        }
    }

    // check increment button
    if (IncButton.isShortPressDetected())
    {
        if (_state == COUNTING)
        {
            if (_number + 1 <= COUNTER_MAX_VALUE) _number++;
            delay(200); // Delay to avoid rapid number changes
        }
        else if (_state == SETTING_THRESHOLD)
        {
            if (_threshold + 1 <= COUNTER_MAX_VALUE) _threshold++;
            delay(200); // Delay to avoid rapid changes
        }
    }
    else if (IncButton.isLongPressDetected())
    {
        if (_state == COUNTING)
        {
            if (_number + 10 <= COUNTER_MAX_VALUE) _number = _number + 10;
            delay(200); // Delay to avoid rapid number changes
        }
        else if (_state == SETTING_THRESHOLD)
        {
            if (_threshold + 10 <= COUNTER_MAX_VALUE) _threshold = _threshold + 10;
            delay(200); // Delay to avoid rapid changes
        }
    }

    // check threshold button
    if (ThdButton.isShortPressDetected())
    {
        if (_state == COUNTING)
        {
            // Set counter state to SETTING_THRESHOLD and enable green LED
            _state = SETTING_THRESHOLD;
            digitalWrite(PIN_LED_GREEN, HIGH);
            //_number = 0; // Reset the counter value to zero
        }
        else if (_state == SETTING_THRESHOLD)
        {
            // Set counter state to COUNTING and disable green LED
            _state = COUNTING;
            digitalWrite(PIN_LED_GREEN, LOW);
            if (_number >= _threshold) _number = _threshold;
            Buzzer.notification(); // notify that the threshold is set
        }
        else if (_state == ALARM)
        {
            _state = COUNTING;
            Buzzer.disable();
            _threshold = COUNTER_MAX_VALUE;
            digitalWrite(PIN_LED_RED, LOW);
        }
    }
    else if (ThdButton.isLongPressDetected())
    {
        if (_state == SETTING_THRESHOLD)
            _threshold = _number;
    }
    // Check if counter exceeds threshold
    if (_state == COUNTING && _number > _threshold)
        _state = ALARM;

    this->update_EEPROM();
}


// feeds number into shift register (simplifies code)
void TallyCounter::update_shift_reg(byte output)
{
    digitalWrite(PIN_SR_LATCH, LOW);
    shiftOut(PIN_SR_DATA, PIN_SR_CLK, MSBFIRST, output);
    digitalWrite(PIN_SR_LATCH, HIGH);
}

void TallyCounter::display_number()
{
    uint16_t num = (this->_state == SETTING_THRESHOLD) ? this->_threshold : this->_number;

    // split num by digits
    byte ones = num % 10;
    byte tens = (num / 10) % 10;
    byte hundreds = (num / 100) % 10;

    // display ones
    _data = B00000000;
    update_shift_reg(_data);         // clear shift register
    _data = _data | B00000001;        // Enable 1st display
    _data = _data | (ones << 3);      // set tens digit
    update_shift_reg(_data);
    delay(WAIT);          

    // display tens
    _data = B00000000;
    update_shift_reg(_data);
    _data = _data | B00000010;        // enable 2nd display
    _data = _data | (tens << 3);      // set tens digit
    update_shift_reg(_data);
    delay(WAIT);

    // display hundreds
    _data = B00000000;
    update_shift_reg(_data);
    _data = _data | B00000100;        // enable 3rd display
    _data = _data | (hundreds << 3);      // set hundreds digit
    update_shift_reg(_data);
    delay(WAIT);
}

// plays alarm
void TallyCounter::play_alarm()
{
    Buzzer.alarm();
    this->read_buttons();
}

// updates EEPROM
void TallyCounter::update_EEPROM()
{
    _boot = true;
    EEPROM.put(ADDR_NUM, _number);
    EEPROM.put(ADDR_THR, _threshold);
    EEPROM.put(ADDR_BOOT, _boot);
    EEPROM.put(ADDR_STATE, _state);
}

// loads number and threshold from EEPROM on boot
void TallyCounter::load_EEPROM()
{
    _boot = EEPROM.read(ADDR_BOOT);
    if (_boot)
    {
        EEPROM.get(ADDR_NUM, _number);
        EEPROM.get(ADDR_THR, _threshold);
        EEPROM.get(ADDR_STATE, _state);
    }
}

// get current state
state_t TallyCounter::get_state()
{
    return _state;
}