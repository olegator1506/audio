#ifndef __PCF_H__
#define __PCF_H__
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
extern bool pcfInit(void);
extern bool pcfSelAnalogInput(uint8_t inputNum);
extern bool pcfSelRegulator(uint8_t chNum);
#ifdef __cplusplus
}
#endif
#endif
