#ifndef __ADAU17X_H__
#define __ADAU17X_H__
extern void adauSetChipAddress(uint8_t address);
extern bool  adauInit(uint8_t chipAddress);
extern bool adauWrite(uint16_t addr,const uint8_t *data, size_t len);
extern bool adauRead(uint16_t addr,uint8_t *data, size_t len); 
extern bool adauDspOff(void);
extern bool adauDspOn(void);
extern bool adauDspReload(void);
extern bool adauOutVol(int level, bool line);
extern float adau523toFloat(uint8_t *data);
extern bool adauEqSet(uint8_t band, int8_t level);
extern bool  adauReadLevel(float *left, float *right);
extern bool adauI2sOn(void);
extern bool adauI2sOff(void);
extern bool adauLoadProgram(void);

#endif