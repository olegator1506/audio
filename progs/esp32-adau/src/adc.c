#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <driver/gpio.h>
#include <math.h>

#define ADC_CHANNEL_EQ ADC_CHANNEL_6
#define ADC_WIDTH_EQ ADC_WIDTH_BIT_12
#define ADC_ATTEN_EQ ADC_ATTEN_MAX
#define NO_OF_SAMPLES 10

static uint _raw2Val(uint32_t sum) {
    uint val = round((float)(sum) / (float)(NO_OF_SAMPLES) / 5.);
    return round((float)(val >> 2) / 10.);
}
/* 
void app_main() {
    static const adc_channel_t channel = ADC_CHANNEL_EQ;
    static const adc_atten_t atten = ADC_ATTEN_EQ;
    adc1_config_width(ADC_WIDTH_EQ);
    adc1_config_channel_atten(channel, atten);
    while(1){
        uint32_t sum = 0;
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            sum += adc1_get_raw((adc1_channel_t)channel);
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        uint val = _raw2Val(sum);
        ESP_LOGI("ADC","Sum = %d Val = %d",sum,val);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}  */