#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_system.h"
#include <driver/adc.h>
#include "display.h"
#include <math.h>
//#include <soc/sens_reg.h>
//#include <soc/sens_struct.h>


#define TIMER_DIVIDER         800  //  Частота CLK таймера 100 Кгц (80 Мгц / 800)
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
#define TIMER_INTERVAL   (0.001)   // sample test interval for the second timer
#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload
#define VU_SAMPLE_COUNT 100
#define VU_LEVEL_DIVIDER 20 // Преобразование значения ADC в % громкости (Level =ADC /VU_LEVEL_DIVIDER);
// Входы аудиосигнала
#define VU_ADC_CH_LEFT ADC1_CHANNEL_4 // IO32
#define VU_ADC_CH_RIGHT ADC1_CHANNEL_6 // IO34

#define VU_0DB_LEVEL 1.5 //уровень напряжения принимаемый за 0 dB

portMUX_TYPE DRAM_ATTR timerMux = portMUX_INITIALIZER_UNLOCKED;
uint32_t _vuSum[2] = {0,0}; // Здесь суммируем отсчеты ADC
uint16_t _vuSampleCnt = 0; // количество отcчетов, по достижении VU_SAMPLE_COUNT генерим событие и сбрасываем сумматор и счетчик

static const char *TAG="vu-meter";
/*
int IRAM_ATTR local_adc1_read(int channel) {
    uint16_t adc_value;
    SENS.sar_meas_start1.sar1_en_pad = (1 << channel); // only one channel is selected
    while (SENS.sar_slave_addr1.meas_status != 0);
    SENS.sar_meas_start1.meas1_start_sar = 0;
    SENS.sar_meas_start1.meas1_start_sar = 1;
    while (SENS.sar_meas_start1.meas1_done_sar == 0);
    adc_value = SENS.sar_meas_start1.meas1_data_sar;
    return adc_value;
}
*/

static float adcToDb(uint16_t adcVal) {
    if(adcVal == 0 ) return -21;
    float volt =  adcVal * 0.71  /1000; 
    float db = 20 * log10(volt / VU_0DB_LEVEL);
    return db;
}

static void vuTask(void *arg)
{
     uint16_t left,right;
    while (1) {
        vTaskDelay(1);
        adc1_config_channel_atten(VU_ADC_CH_LEFT,ADC_ATTEN_DB_0);
        adc1_config_channel_atten(VU_ADC_CH_RIGHT,ADC_ATTEN_DB_0);
        _vuSum[0] += adc1_get_raw(VU_ADC_CH_LEFT);
        _vuSum[1] += adc1_get_raw(VU_ADC_CH_RIGHT);
//    _vuSum[0] += local_adc1_read(VU_ADC_CH_LEFT);
//    _vuSum[1] += local_adc1_read(VU_ADC_CH_RIGHT);
        _vuSampleCnt++;
        if(_vuSampleCnt == VU_SAMPLE_COUNT) {
            left = _vuSum[0] / VU_SAMPLE_COUNT;
            right = _vuSum[1] / VU_SAMPLE_COUNT;
            displaySetLevelDb(0,adcToDb(left));
            displaySetLevelDb(1,adcToDb(right));
//        printf("%f %f\n",adcToDb(evt.left),adcToDb(evt.right));
//          printf("%d %d\n",left, right);
            _vuSampleCnt = 0;
            _vuSum[0] = 0;
            _vuSum[1] = 0;
        }

    }
}

esp_err_t vuMeterInit(void){
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(VU_ADC_CH_LEFT,ADC_ATTEN_DB_0);
    adc1_config_channel_atten(VU_ADC_CH_RIGHT,ADC_ATTEN_DB_0);
    xTaskCreate(vuTask, "timer_evt_task", 2048, NULL, 5, NULL);
    ESP_LOGI(TAG,"Task started");
    return ESP_OK;
}
