/**
 * Модуль обмена с чипами PCF8574
 **/ 
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <config.h>
#include <i2c.h>

static const char *TAG = "pcf";
#define I2C_ADDRESS_CH_SWITCH 0x20
#define I2C_RETRY_COUNT 1
#define I2C_RETRY_TIMEOUT 1

static bool _i2cWriteCheck(uint8_t byte_wr){
    bool result;
    uint8_t br;
    result = false;
    for(int retry =0; retry < I2C_RETRY_COUNT;retry++) {
        if( i2cWrite(I2C_ADDRESS_CH_SWITCH, &byte_wr, 1) == ESP_OK) {
            result = true;break;
        }
//        vTaskDelay(I2C_RETRY_TIMEOUT / portTICK_PERIOD_MS);
    }
    if(!result) return false;
    for(int retry =0; retry < I2C_RETRY_COUNT;retry++) {
        if(i2cRead(I2C_ADDRESS_CH_SWITCH,&br,1) == ESP_FAIL){
//            vTaskDelay(I2C_RETRY_TIMEOUT / portTICK_PERIOD_MS);
            continue;
        }
        if(br == byte_wr) return true;
    }    
    return false;    
}



static uint8_t _pcfSwitchByte = 0;
esp_err_t pcfSelAnalogInput(uint8_t inputNum){
    if(inputNum >3) {
        ESP_LOGE(TAG,"Invalid analog input number %d",inputNum);
        return ESP_FAIL;
    }
    uint8_t b = (_pcfSwitchByte & 0x3f) + (inputNum << 6);
    ESP_LOGI(TAG,"Set analog input #%d PCF byte %02x",inputNum,b);
    if( b == _pcfSwitchByte) return ESP_OK; // Биты не изменились
    if(!_i2cWriteCheck(b)) return ESP_FAIL;
    _pcfSwitchByte = b;
    return ESP_OK;
}

esp_err_t pcfSelRegulator(uint8_t chNum){
    if(chNum >7) {
        ESP_LOGE(TAG,"Invalid regulator number %d",chNum);
        return ESP_FAIL;
    }
    uint8_t b = (_pcfSwitchByte & 0xf8) + chNum;
    ESP_LOGI(TAG,"Select regulator #%d PCF byte %02x",chNum,b);
    if( b == _pcfSwitchByte) return ESP_OK; // Биты не изменились
    if(!_i2cWriteCheck(b)) return ESP_FAIL;
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
