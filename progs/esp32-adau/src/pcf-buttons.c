#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_event.h>
#include <string.h>
#include <nvs_flash.h>
// Project includes
#include "config.h"
#include "common.h"
#include "i2c.h"
/*
static const char *TAG="BUTTONS";

static bool _getState(uint8_t pcfState, uint8_t bit) {
    return ((pcfState & (1<<bit)) ==0);
}

static void _buttonsTask(void *pvParameters) {
    bool btState[PCF_BUTTONS_COUNT];
    uint8_t bitNums[PCF_BUTTONS_COUNT] = PCF_BUTTONS_BITS;
    uint8_t pcfByte;
    TMainEvent evt;

    i2cRead(I2C_ADDRESS_PCF1, &pcfByte,1 );
    for(int i =0;i<PCF_BUTTONS_COUNT;i++)
        btState[i] = _getState(pcfByte,bitNums[i]);
    while(1){
        vTaskDelay( PCF_BUTTONS_POLL_PERIOD / portTICK_PERIOD_MS);
        if(i2cRead(I2C_ADDRESS_PCF1, &pcfByte,1 ) != ESP_OK){
            ESP_LOGE(TAG,"Error reading from PCF chip");
            continue;
        }
        for(int i =0;i<PCF_BUTTONS_COUNT;i++) {
            bool state = _getState(pcfByte,bitNums[i]);
            if(state != btState[i]){
                ESP_LOGI(TAG,"Btn %d %s",i, state ? "pressed":"released");
                evt.code = state ? MY_EVENT_BUTTON_PRESSED : MY_EVENT_BUTTON_RELEASED;
                evt.param = i;
                xQueueSend(mainQ, (void *)&evt,10);
                btState[i] = state;
            }
        }    
    }    

}

esp_err_t pcfButtonsInit(void){
    uint8_t b = 0xff;
    if(i2cWrite(I2C_ADDRESS_PCF1, &b,1 ) != ESP_OK){
        ESP_LOGE(TAG,"Error writing data to PCF chip");
        return ESP_FAIL;
    }

    if(xTaskCreate(_buttonsTask, "PCF_BUTTONS_TASK", 2048, NULL, 5, NULL ) != pdPASS) {
        ESP_LOGE(TAG,"Start failed: error creating task ");    
        return ESP_FAIL;
    }
    return ESP_OK;
}
*/

