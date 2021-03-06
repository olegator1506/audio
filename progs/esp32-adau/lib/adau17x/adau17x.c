#include <stdlib.h>
#include <string.h>
#include <esp_err.h>
#include <esp_log.h>

#include "config.h"
#include "i2c.h"
#include "projects/sample-direct_IC_1.h"
#include "projects/sample-direct_IC_1_PARAM.h"
#include "eq/80.h"
#include "eq/230.h"
#include "eq/910.h"
#include "eq/3k6.h"
#include "eq/10k.h"
#include "eq/14k.h"







// Абсолютные значения положения движков эквалайзера (0 - середина)
#define EQ_LEVEL_MIN -10 
#define EQ_LEVEL_MAX 10
#define EQ_MAX_BAND_NUM 5
const char *TAG = "adau";
static uint8_t _address;

char *_adauLoadError = NULL;
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

static char *_dbgDataStr(const uint8_t *data, int len) {
  static char s[255];
  int l = len;
  if(l >20) l =20;
  memset(s,0,255);
  for(int i=0;i<l;i++)
    sprintf(s+i*3,"%02X ",data[i]);
  return s;  
}

static void _changeByteOrder(uint32_t data, uint8_t *result){
  result[3] = data & 0xff;
  result[2] = (data >>8) & 0xff;  
  result[2] = (data >>16) & 0xff;  
  result[0] = (data >>24) & 0xff;  
}

float adau523toFloat(uint8_t *data){
  uint8_t sign = data[0] & 0x08;
  int sum =0;
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
esp_err_t adauWrite(uint16_t addr,const uint8_t *data, size_t len) {
  ESP_LOGI(TAG,"W: %d bytes at address %04X : %s",len,addr,_dbgDataStr(data,len));
  uint8_t *bw = (uint8_t *)malloc(len +2);
  if(!bw){
      ESP_LOGE(TAG,"Memeory allocation error");
      return ESP_FAIL;
  }
  esp_err_t res;
  bw[0] = ( addr >> 8 ) & 0xff;
  bw[1] = addr & 0xff;
  memcpy(bw+2,data,len);
  res =  i2cWrite(_address,bw,len+2);
  if(res != ESP_OK) 
    ESP_LOGE(TAG,"I2C Write error.");
  free(bw);
  return res;
}
/**
 * @summary Считывает данные из чипа
 * @param addr начальный адрес регистра
 * @param data адрес блока данных
 * @param len длинна блока данных
 **/ 

esp_err_t adauRead(uint16_t addr,uint8_t *data, size_t len) {
  uint8_t bw[2];

  bw[0] = ( addr >> 8 ) & 0xff;
  bw[1] = addr & 0xff;
  if(i2cWrite(_address,bw,2) != ESP_OK) {
    ESP_LOGE(TAG,"Read error on I2C write register/memory address.");
    return ESP_FAIL;
  }
  if(i2cRead(_address, data,len) != ESP_OK) {
    ESP_LOGE(TAG,"Read error on I2C read data.");
    return ESP_FAIL;
  }
  ESP_LOGI(TAG,"R: %d bytes at address %04X : %s",len,addr,_dbgDataStr(data,len));
  return ESP_OK;
}
/**
 * @summary  Записывает данные методом SafeLoad в память чипа
 *    данные - 32 битные слова (младший байт первый)
 * @param address - 32 битный адрес первого  регистра
 * @param data - байтовый массив данных
 * @param length - длина блока данных в словах(!) т.е. при записи 20 байт length = 5
 **/

esp_err_t adauSafeLoad(const uint8_t *data, const uint32_t address, const uint32_t length) {
  uint8_t addrBlock[8];
  _changeByteOrder(address-1,addrBlock);
  _changeByteOrder(length,addrBlock+4);
  if(adauWrite(1, data, length * 4) != ESP_OK) return ESP_FAIL;
  if(adauWrite(6,addrBlock,8) != ESP_OK) return ESP_FAIL;
  return ESP_OK;
}

int32_t SIGMA_WRITE_REGISTER_BLOCK(uint8_t devAddress, uint16_t address, uint16_t length, ADI_REG_TYPE *pData)
{
//  DBG("SIGMA WRITE Device addres %02X Register %04X Length %d %02X",devAddress, address,length,pData[0]);
  if(adauWrite(address,pData, length) == ESP_OK)  return 0;
  _adauLoadError = malloc(256);
  snprintf(_adauLoadError,255,"Error writing block. Address %04X Size %d", address, length);
  return -1;
}

/* Установка усиления входного микшера по входу AUX
Val = 0 - mute 5 - 0dB  7 - 6dB
*/
esp_err_t  adauAuxInGain(uint8_t val)
{
  uint8_t data[2];
  uint16_t regs[2] = {
    REG_RECORD_MIXER_LEFT_CTRL_1_IC_1_ADDR, // 0x400b
    REG_RECORD_MIXER_RIGHT_CTRL_1_IC_1_ADDR // 0x400d
  };
  if(val>7) val =7;
  for(uint8_t i=0; i<2;i++) {
    if(adauRead(regs[i],data+i,1) != ESP_OK ) return ESP_FAIL;
    data[i] = (data[i] & 0xf8 ) + val;
    if(adauWrite(regs[i],data+i,1) != ESP_OK ) return ESP_FAIL;
  }
  return ESP_OK;
}
esp_err_t adauDspOff(void) {
  ESP_LOGI(TAG,"DSP Off");
  uint8_t data[4] = {
    0x01, // 0x401c : left mixer 3 enable, left & right dac Off
    0x06, // 0x401d ; Right bypass gain mute, left bypass gain 0 dB
    0x01, // 0x401e : Right mixer 4 enable, left & right dac Off
    0x60, // 0x401f ; Left bypass gain mute, Right bypass gain 0 dB
  }, b=0;
  if(adauWrite(REG_PLAYBACK_MIXER_LEFT_CONTROL_0_IC_1_ADDR,data,4)!= ESP_OK ) return ESP_FAIL; // Переключаем вход с DAC- а на микшер
  if(adauWrite(REG_DSP_RUN_REGISTER_IC_1_ADDR,&b,1)!= ESP_OK ) return ESP_FAIL; // Останавливаем DSP
  if(adauWrite(REG_DSP_ENABLE_REGISTER_IC_1_ADDR,&b,1)!= ESP_OK ) return ESP_FAIL; // Блокируем DSP
  return ESP_OK;
}
esp_err_t adauDspOn(void) {
  uint8_t data[4] = {
    0x21, // 0x401c : left mixer 3 enable, left dac  On (Unmute), right dac off (mute)
    0x00, // 0x401d ; Left & Right bypass gain mute
    0x41, // 0x401e : Right mixer 4 enable, left & right dac Off
    0x00, // 0x401f ; Left bypass gain mute, Right bypass gain 0 dB
  }, b = 1;
  ESP_LOGI(TAG,"DSP On");
  if(adauWrite(REG_DSP_ENABLE_REGISTER_IC_1_ADDR,&b,1)!= ESP_OK ) return ESP_FAIL; // Разблокируем DSP
  if(adauWrite(REG_DSP_RUN_REGISTER_IC_1_ADDR,&b,1)!= ESP_OK ) return ESP_FAIL; // Запускаем DSP
  if(adauWrite(REG_PLAYBACK_MIXER_LEFT_CONTROL_0_IC_1_ADDR,data,4)!= ESP_OK ) return ESP_FAIL; // Переключаем вход с микшера на ЦАП 
  return ESP_OK;
}

esp_err_t adauDspReload(void) {
  ESP_LOGI(TAG,"DSP reload program");
//  default_download_IC_1();
  return ESP_OK;
}
// Устанавливает уровень уровень громкости 
// level 0: -57dB, 63: +6dB 
// line = true - уровень громкости линейного выхода, false - наушники

esp_err_t adauOutVol(int level, bool line) {
  uint8_t data[2],b;
  uint16_t addr;
  if(level > 0x3f) level = 0x3f;
  else if(level < 0) level = 0;
  addr = line ? REG_PLAYBACK_LINE_OUT_LEFT_IC_1_ADDR : REG_PLAYBACK_HEADPHONE_LEFT_IC_1_ADDR;
  if(adauRead(addr,data,2) != ESP_OK ) return ESP_FAIL;
  b = ((level & 0x3f) << 2);
  for(int i=0;i<2;i++)  data[i] = (data[i] & 3) | b;
  ESP_LOGI(TAG,"Set level for %s to %d (L:%02X R:%02X)",line ? "line output":"head phones",level,data[0],data[1]);
  if(adauWrite(addr,data,2) != ESP_OK ) return ESP_FAIL;
  return ESP_OK;
}

esp_err_t adauEqSet(uint8_t band, int8_t level) {
  uint32_t paramAddr;
  if(band > EQ_MAX_BAND_NUM) {
    ESP_LOGE(TAG,"Invalid EQ band number %d",band);
    return ESP_FAIL;
  }  
  paramAddr = 12 + (band * 5);
  ESP_LOGI(TAG,"EQ set band %d level %d",band,level);
  if(level < EQ_LEVEL_MIN) level = EQ_LEVEL_MIN;
  if(level > EQ_LEVEL_MAX) level = EQ_LEVEL_MAX;
  int offs = (level - EQ_LEVEL_MIN) * 20;
  const uint8_t *data = _eqData[band] + offs; 
  return adauSafeLoad(data,paramAddr,(const uint32_t)5);
}

esp_err_t adauReadLevel(float *left, float *right){
  uint8_t data[4];
  if(adauRead(MOD_READBACK1_READBACKALGSIGMA2001_ADDR,data,4) != ESP_OK ) return ESP_FAIL;
  *left = adau523toFloat(data);
  if(adauRead( MOD_READBACK2_READBACKALGSIGMA2002_ADDR,data,4) != ESP_OK ) return ESP_FAIL;
  *right = adau523toFloat(data);
  return ESP_OK;
}

static esp_err_t _i2sSwitch(bool state){

  uint8_t param0[4] = {0,0,0,0}, param1[4] = {0,0,0,0};
  if(state) 
    param1[1] = 0x80;
  else
    param0[1] = 0x80;
  ESP_LOGI(TAG,"I2s input switch %s",state ? "ON":"OFF");
  if(adauWrite(MOD_NX2_1_ALG0_STAGE0_STEREOSWITCHNOSLEW_ADDR,param0,4) != ESP_OK ) return ESP_FAIL;
  if(adauWrite(MOD_NX2_1_ALG0_STAGE1_STEREOSWITCHNOSLEW_ADDR,param1,4) != ESP_OK ) return ESP_FAIL;
  return ESP_OK;
}

esp_err_t adauI2sOn(void){
  return _i2sSwitch(true);
}

esp_err_t adauI2sOff(void){
  return _i2sSwitch(false);
}

esp_err_t adauLoadProgram(void){
    if(_adauLoadError) free(_adauLoadError);
    _adauLoadError = NULL;
    default_download_IC_1();
    if(_adauLoadError) {
      ESP_LOGE(TAG,"Program load error: %s",_adauLoadError);
      free(_adauLoadError);
      _adauLoadError = NULL;
      return ESP_FAIL;
    }
    return ESP_OK;
}

void adauSetChipAddress(uint8_t address) {
  _address = address;
}
esp_err_t adauInit(uint8_t chipAddress) { 
    adauSetChipAddress(chipAddress);
    if( adauLoadProgram() == ESP_FAIL) return ESP_FAIL;
//    adauAuxInGain(7);
// настройки гроскости (перенести в проект !)
//    adauOutVol(30,true);
//    adauOutVol(63,false);
    adauI2sOff();
  return ESP_OK;
}
