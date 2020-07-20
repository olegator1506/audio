/**
 * Модуль обмена с чипами PCF8574
 **/ 
#include <config.h>
#include <i2c.h>

#define I2C_ADDRESS_CH_SWITCH 0x20

static uint8_t _pcfSwitchByte = 0;
esp_err_t pcfSelAnalogInput(uint8_t inputNum){
    uint8_t b = (_pcfSwitchByte & 0x3f) + (inputNum << 6);
    if( b == _pcfSwitchByte) return ESP_OK; // Биты не изменились
    if( i2cWrite(I2C_ADDRESS_CH_SWITCH, &b, 1) == ESP_FAIL) return ESP_FAIL;
    _pcfSwitchByte = b;
    return ESP_OK;
}
// Инициализация чипов PCF8574 (коммутатор входов+опрос регуляторов, опрос кнопок, управление светодиодами)
esp_err_t pcfInit(void){
    _pcfSwitchByte = 0;
    if(i2cWrite(I2C_ADDRESS_CH_SWITCH,&_pcfSwitchByte,1) == ESP_FAIL) return ESP_FAIL;
    return ESP_OK;
}
