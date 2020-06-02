#include <twi.h>
#include <stdlib.h>
#include "config.h"
#include "debug.h"
#include "adau_project.h"
#include "my-project2_IC_1_PARAM.h"
#include "eq/80.h"
#include "eq/230.h"
#include "eq/910.h"
#include "eq/3k6.h"
#include "eq/10k.h"
#include "eq/14k.h"




// Абсолютные значения положения движков эквалайзера (0 - середина)
#define EQ_LEVEL_MIN -10 
#define EQ_LEVEL_MAX 10
/*
typedef enum {
  EQ_BAND_80 = 0
} TEqBand;
*/
const uint8_t *_eqData[] = {
  eqBand80,
  eqBand230,
  eqBand910,
  eqBand3k6,
  eqBand10k,
  eqBand14k
};

static void _changeByteOrder(uint32_t data, uint8_t *result){
  result[3] = data & 0xff;
  result[2] = (data >>8) & 0xff;  
  result[2] = (data >>16) & 0xff;  
  result[0] = (data >>24) & 0xff;  
}

float adau523toFloat(uint8_t *data){
  uint8_t sign = data[0] & 0x08;
  int32 sum =0;
  for(int i=0;i<4;i++) sum = (sum << 8) + (sign ? data[i] ^ 0xff : data[i]);
  float result = sum / 8388606.;
  if(sign) result = result * -1.;
  return result;
}



/**
 * @description Записывает данные в чип
 * @param addr начальный адрес регистра
 * @param data блок данных
 * @param len длинна блока данных
 **/ 
uint8_t adauWrite(uint16_t addr,const uint8_t *data, size_t len) {
  DBG("W: %d bytes at address %04X : %s",len,addr,dbgDataStr(data,len));
  uint8_t *bw = (uint8_t *)malloc(len +2);
  uint8_t res;
  bw[0] = ( addr >> 8 ) & 0xff;
  bw[1] = addr & 0xff;
  memcpy(bw+2,data,len);
  res = twi_writeTo(ADAU_ADDRESS,bw,len+2,1);
  if(res) DBG("Write error.code %d",res);
  free(bw);
  return res;
}


esp_err_t adauRead(uint16_t addr,uint8_t *data, size_t len) {
  uint8_t bw[2];
  uint8_t res;

  bw[0] = ( addr >> 8 ) & 0xff;
  bw[1] = addr & 0xff;
  res = twi_writeTo(ADAU_ADDRESS,bw,2,0);
  if(res) {
    DBG("Read error. Code %d",res);
    return res;
  }
  res = twi_readFrom(ADAU_ADDRESS, data,len,1);
  if(res) {
    DBG("Read error. Code %d",res);
    return res;
  }
  DBG("R: %d bytes at address %04X : %s",len,addr,dbgDataStr(data,len));
  return 0;
}
/**
 * @summary  Записывает данные методом SafeLoad в память чипа
 *    данные - 32 битные слова (младший байт первый)
 * @param address - 32 битный адрес первого  регистра
 * @param data - байтовый массив данных
 * @param length - длина блока данных в словах(!) т.е. при записи 20 байт length = 5
 **/

uint8_t adauSafeLoad(const uint8_t *data, const uint32_t address, const uint32_t length) {
  uint8_t addrBlock[8];
  _changeByteOrder(address-1,addrBlock);
  _changeByteOrder(length,addrBlock+4);
  adauWrite(1, data, length * 4);
  adauWrite(6,addrBlock,8);
}

int32_t SIGMA_WRITE_REGISTER_BLOCK(uint8_t devAddress, uint16_t address, uint16_t length, ADI_REG_TYPE *pData)
{
//  DBG("SIGMA WRITE Device addres %02X Register %04X Length %d %02X",devAddress, address,length,pData[0]);
  adauWrite(address,pData, length);
  return 0;
}

/* Установка усиления входного микшера по входу AUX
Val = 0 - mute 5 - 0dB  7 - 6dB
*/
void  adauAuxInGain(uint8_t val)
{
  uint8_t data[2];
  uint16_t regs[2] = {
    REG_RECORD_MIXER_LEFT_CTRL_1_IC_1_ADDR, // 0x400b
    REG_RECORD_MIXER_RIGHT_CTRL_1_IC_1_ADDR // 0x400d
  };
  if(val>7) val =7;
  for(uint8_t i=0; i<2;i++) {
    adauRead(regs[i],data+i,1);
    data[i] = (data[i] & 0xf8 ) + val;
    adauWrite(regs[i],data+i,1);
  }
}
void adauDspOff(void) {
  DBG("ADAU DSP Off");
  uint8_t data[4] = {
    0x01, // 0x401c : left mixer 3 enable, left & right dac Off
    0x06, // 0x401d ; Right bypass gain mute, left bypass gain 0 dB
    0x01, // 0x401e : Right mixer 4 enable, left & right dac Off
    0x60, // 0x401f ; Left bypass gain mute, Right bypass gain 0 dB
  }, b=0;
  adauWrite(REG_PLAYBACK_MIXER_LEFT_CONTROL_0_IC_1_ADDR,data,4); // Переключаем вход с DAC- а на микшер
  adauWrite(REG_DSP_RUN_REGISTER_IC_1_ADDR,&b,1); // Останавливаем DSP
  adauWrite(REG_DSP_ENABLE_REGISTER_IC_1_ADDR,&b,1); // Блокируем DSP
  data[0] = 0; 
}
void adauDspOn(void) {
  uint8_t data[4] = {
    0x21, // 0x401c : left mixer 3 enable, left dac  On (Unmute), right dac off (mute)
    0x00, // 0x401d ; Left & Right bypass gain mute
    0x41, // 0x401e : Right mixer 4 enable, left & right dac Off
    0x00, // 0x401f ; Left bypass gain mute, Right bypass gain 0 dB
  }, b = 1;
  DBG("ADAU DSP On");
  adauWrite(REG_DSP_ENABLE_REGISTER_IC_1_ADDR,&b,1); // Разблокируем DSP
  adauWrite(REG_DSP_RUN_REGISTER_IC_1_ADDR,&b,1); // Запускаем DSP
  adauWrite(REG_PLAYBACK_MIXER_LEFT_CONTROL_0_IC_1_ADDR,data,4); // Переключаем вход с микшера на ЦАП 
}

void adauDspReload(void) {
  DBG("ADAU DSP reload program");
  default_download_IC_1();
}
// Устанавливает уровень уровень громкости 
// level 0: -57dB, 63: +6dB 
// line = true - уровень громкости линейного выхода, false - наушники

void adauOutVol(int level, bool line) {
  uint8_t data[2],b;
  uint16_t addr;
  if(level > 0x3f) level = 0x3f;
  else if(level < 0) level = 0;
  addr = line ? REG_PLAYBACK_LINE_OUT_LEFT_IC_1_ADDR : REG_PLAYBACK_HEADPHONE_LEFT_IC_1_ADDR;
  adauRead(addr,data,2);
  b = ((level & 0x3f) << 2);
  for(int i=0;i<2;i++)  data[i] = (data[i] & 3) | b;
  DBG("ADAU set level for %s to %d (L:%02X R:%02X)",line ? "line output":"head phones",level,data[0],data[1]);
  adauWrite(addr,data,2);  
}

void adauEqSet(uint8_t band, int8_t level) {
  uint32_t paramAddr;
  if(band >4) return;
  paramAddr = 12 + (band * 5);
  DBG("EQ set band %d level %d",band,level);
  if(level < EQ_LEVEL_MIN) level = EQ_LEVEL_MIN;
  if(level > EQ_LEVEL_MAX) level = EQ_LEVEL_MAX;
  int offs = (level - EQ_LEVEL_MIN) * 20;
  const uint8_t *data = _eqData[band] + offs; 
  adauSafeLoad(data,paramAddr,(const uint32_t)5);
}

bool adauReadLevel(float *left, float *right){
  uint8_t data[4];
  if(adauRead(MOD_READBACK1_READBACKALGSIGMA2001_ADDR,data,4) !=0 ) return false;
  *left = adau523toFloat(data);
  if(adauRead( MOD_READBACK2_READBACKALGSIGMA2002_ADDR,data,4) != 0) return false;
  *right = adau523toFloat(data);
  return true;
}
void adauInit(void) {
    twi_init(SDA_PIN,SCL_PIN);
    twi_setClock(I2C_FR);
    default_download_IC_1();
//    adauAuxInGain(7);
// настройки гроскости (перенести в проект !)
//    adauOutVol(30,true);
//    adauOutVol(30,false);
}
