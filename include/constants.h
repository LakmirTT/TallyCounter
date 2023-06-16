#ifndef CONSTANTS_H
#define CONSTANTS_H

// pinout
#define PIN_BUTTON_THD 8
#define PIN_BUTTON_DEC 9
#define PIN_BUTTON_INC 10

#define PIN_LED_RED 12 
#define PIN_LED_GREEN 13

#define PIN_BUZZER 11

#define PIN_SR_CLK 5
#define PIN_SR_DATA 3
#define PIN_SR_LATCH 4

// maximum value of counter
#define COUNTER_MAX_VALUE 999
// minimum value of counter
#define COUNTER_MIN_VALUE 0
// default threshold
#define DEFAULT_THD_VALUE 410

// long press interval in milliseconds
#define LONG_PRESS_INTERVAL 500
// output delay in milliseconds
#define WAIT 5

//default alarm time in milliseconds
#define DEFAULT_ALARM_TIME 5

// number value address in EEPROM
#define ADDR_NUM 0
// threshold value address in EEPROM
#define ADDR_THR (ADDR_NUM + sizeof(uint16_t))
// boolean value address in EEPROM
#define ADDR_BOOT (ADDR_THR + sizeof(uint16_t))
// state_t value address in EEPROM
#define ADDR_STATE (ADDR_BOOT + sizeof(bool))

#endif