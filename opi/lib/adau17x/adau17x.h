#ifndef __ADAU17X_H__
#define __ADAU17X_H__
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
void adauSetChipAddress(uint8_t address);
bool  adauInit(uint8_t chipAddress);
bool adauWrite(uint16_t addr,const uint8_t *data, size_t len);
bool adauRead(uint16_t addr,uint8_t *data, size_t len); 
bool adauDspOff(void);
bool adauDspOn(void);
bool adauDspReload(void);
bool adauOutVol(int level, bool line);
float adau523toFloat(uint8_t *data);
int32_t floatToDsp( float x );
int32_t dbToDsp( float x );
bool adauEqSet(uint8_t band, int8_t level);
bool  adauReadLevel(float *left, float *right);
bool adauI2sOn(void);
bool adauI2sOff(void);
bool adauLoadProgram(void);
#ifdef __cplusplus
}
#endif

#endif