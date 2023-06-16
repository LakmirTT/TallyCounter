#include <Arduino.h>

#include "TallyCounter.h"

TallyCounter *counter = new TallyCounter(PIN_BUTTON_INC, PIN_BUTTON_DEC, PIN_BUTTON_THD, PIN_BUZZER);

void setup() 
{
	counter->enable_pins();
	counter->update_shift_reg(0); // clear
	counter->load_EEPROM();
}

void loop() 
{
	counter->read_buttons();
	switch (counter->get_state())
	{
	case COUNTING:
		counter->display_number();
		break;
	case SETTING_THRESHOLD:
		digitalWrite(PIN_LED_GREEN, HIGH);
		counter->display_number();
		break;
	case ALARM:
		counter->play_alarm();
		break;
	default:
		break;
	}
}