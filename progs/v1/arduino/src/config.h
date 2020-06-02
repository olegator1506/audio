#ifndef __CONFIG__
#define __CONFIG__
#include <Arduino.h>
#define TIMER_INIT timer_init_ISR_2KHz(TIMER_DEFAULT)
// период прерываний таймера, мкс (величина обратная частоте таймера F_INTERRUPTS)
#define TIMER_PERIOD 50 
//#define __DEBUG__
#define DEBUG_SERIAL

#define IR_CONTROL_TYPE NONAME1 // тип пульта ДУ (см. ir-codes.h)
#define NONAME1 1
//#include "ir-codes.h"
#define IR_INPUT 13 // вход ИК датчика
#define VU_PIN_LEFT A4
#define VU_PIN_RIGHT A5
#define VU_CH_LEFT 0
#define VU_CH_RIGHT 1
#define VU_MUTE_VAL 500
#define VU_CNT 2000
// Селектор каналов
#define CH_SEL_PINS {9,8,7}
// Энкодер
#define ENCODER_PINS 2,3 
#define CMD_ECODER_PLUS  0xfe 
#define CMD_ECODER_MINUS 0xfd 
#define PINS_PWR {15,16,17,18}
//#define PIN_PWR_AMP 15
//#define PIN_MUTE 16 

#endif