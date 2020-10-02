#ifndef __PCF_H__
#define __PCF_H__
#include <stdint.h>
extern bool pcfInit(void);
extern bool pcfSelAnalogInput(uint8_t inputNum);
extern bool pcfSelRegulator(uint8_t chNum);
#endif
