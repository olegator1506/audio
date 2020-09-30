/**
 * Модуль обмена с чипами PCF8574
 **/ 

#include "i2c/i2c.h"
#include "log/log.h"

static const char *TAG = "pcf";
#define I2C_ADDRESS_CH_SWITCH 0x20




static uint8_t _pcfSwitchByte = 0;
bool pcfSelAnalogInput(uint8_t inputNum){
    if(inputNum >3) {
        LOGE(TAG,"Invalid analog input number %d",inputNum);
        return false;
    }
    uint8_t b = (_pcfSwitchByte & 0x3f) + (inputNum << 6);
    LOGI(TAG,"Set analog input #%d PCF byte %02x",inputNum,b);
    if( b == _pcfSwitchByte) return true; // Биты не изменились
    if(!i2cWriteCheck(I2C_ADDRESS_CH_SWITCH, b)) return false;
    _pcfSwitchByte = b;
    return true;
}

bool pcfSelRegulator(uint8_t chNum){
    if(chNum >7) {
        LOGE(TAG,"Invalid regulator number %d",chNum);
        return false;
    }
    uint8_t b = (_pcfSwitchByte & 0xf8) + chNum;
    LOGI(TAG,"Select regulator #%d PCF byte %02x",chNum,b);
    if( b == _pcfSwitchByte) return true; // Биты не изменились
    if(!i2cWriteCheck(I2C_ADDRESS_CH_SWITCH, b)) return false;
    _pcfSwitchByte = b;
    return true;
}


// Инициализация чипов PCF8574 (коммутатор входов+опрос регуляторов, опрос кнопок, управление светодиодами)

bool pcfInit(void){
    LOGI(TAG,"Init");
    _pcfSwitchByte = 0;
    if(!i2cWrite(I2C_ADDRESS_CH_SWITCH,&_pcfSwitchByte,1)) return false;
    return true;
}
 
