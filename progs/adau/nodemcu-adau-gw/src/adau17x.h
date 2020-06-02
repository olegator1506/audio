#ifndef __ADAU17X_H__
#define __ADAU17X_H__
#include <stddef.h>
#include <stdint.h>
extern void adauInit(void);
extern uint8_t adauWrite(uint16_t addr,const uint8_t *data, size_t len);
extern uint8_t adauRead(uint16_t addr,uint8_t *data, size_t len); 
extern void adauDspOff(void);
extern void adauDspOn(void);
extern void adauDspReload(void);
extern void adauOutVol(int level, bool line);
extern float adau523toFloat(uint8_t *data);
extern void adauEqSet(uint8_t band, int8_t level);
extern bool adauReadLevel(float *left, float *right);


#endif