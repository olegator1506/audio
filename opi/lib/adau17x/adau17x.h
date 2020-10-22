#ifndef __ADAU17X_H__
#define __ADAU17X_H__
#include <stdint.h>
#include <sys/types.h>
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
bool adauEqReset(void);
bool  adauReadLevel(float *left, float *right);
bool adauI2sOn(void);
bool adauI2sOff(void);
bool adauI2sGain(float val);
bool adauLoadProgram(void);
bool adauSuperBass(bool state);
bool adauSelectAnalogInput(uint8_t chNum, int level);
#ifdef __cplusplus
}
#endif

#endif