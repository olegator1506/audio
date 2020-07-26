/**
 * Модуль обмена с чипами PCF8574
 **/ 
#include <esp_log.h>
#include <config.h>
#include <i2c.h>

static const char *TAG = "pcf";
#define I2C_ADDRESS_CH_SWITCH 0x20

static uint8_t _pcfSwitchByte = 0;
esp_err_t pcfSelAnalogInput(uint8_t inputNum){

    uint8_t b = (_pcfSwitchByte & 0x3f) + (inputNum << 6);
    ESP_LOGI(TAG,"Set analog input #%d PCF byte %02x",inputNum,b);
    if( b == _pcfSwitchByte) return ESP_OK; // Биты не изменились
    if( i2cWrite(I2C_ADDRESS_CH_SWITCH, &b, 1) == ESP_FAIL) return ESP_FAIL;
    _pcfSwitchByte = b;
    return ESP_OK;
}
// Инициализация чипов PCF8574 (коммутатор входов+опрос регуляторов, опрос кнопок, управление светодиодами)
esp_err_t pcfInit(void){
    ESP_LOGI(TAG,"Init");
    _pcfSwitchByte = 0;
    if(i2cWrite(I2C_ADDRESS_CH_SWITCH,&_pcfSwitchByte,1) == ESP_FAIL) return ESP_FAIL;
    return ESP_OK;
}
