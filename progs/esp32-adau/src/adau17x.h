#ifndef __ADAU17X_H__
#define __ADAU17X_H__
#include <esp_err.h>
extern esp_err_t  adauInit(void);
extern esp_err_t adauWrite(uint16_t addr,const uint8_t *data, size_t len);
extern esp_err_t adauRead(uint16_t addr,uint8_t *data, size_t len); 
extern esp_err_t adauDspOff(void);
extern esp_err_t adauDspOn(void);
extern esp_err_t adauDspReload(void);
extern esp_err_t adauOutVol(int level, bool line);
extern float adau523toFloat(uint8_t *data);
extern esp_err_t adauEqSet(uint8_t band, int8_t level);
extern esp_err_t  adauReadLevel(float *left, float *right);
extern esp_err_t adauI2sOn(void);
extern esp_err_t adauI2sOff(void);

#endif