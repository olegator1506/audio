#ifndef __PCF_H__
#define __PCF_H__
#include <esp_system.h>
#include <esp_err.h>
extern esp_err_t pcfInit(void);
extern esp_err_t pcfSelAnalogInput(uint8_t inputNum);
extern esp_err_t pcfSelRegulator(uint8_t chNum);
#endif
