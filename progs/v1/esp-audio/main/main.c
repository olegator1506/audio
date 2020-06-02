/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <esp_log.h>
#include <esp_event.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include <time.h>
#include "driver/gpio.h"
// Инклуды проекта
#include "common.h"
#include "mp3.h"
//#include "net.h"
#include "channel.h"
#include "display.h"
#include "st7735.h"
#include "cmd-uart.h"


#define TEST_PIN 27

static const char *TAG="main";
static time_t _lastKeepAlive =0;
QueueHandle_t mainQ;
TMainEvent evt;
TMp3State* mp3State;

//extern esp_err_t vuMeterInit(void);

extern void i2sInit(void);
esp_err_t vuMeterInit(void);

void app_main(void)
{
    bool vuMeterStarted = false;
    displayInit();
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ST7735_WriteString(2,2,"Initialization",Font_7x10,ST7735_BLACK,ST7735_CYAN);
    ESP_ERROR_CHECK(esp_event_loop_create_default());
//    ESP_ERROR_CHECK(netInit());
    i2sInit();
    mainQ = xQueueCreate( 50, sizeof( TMainEvent ) );
    ESP_LOGI(TAG,"Program started");
    cmdUartInit();
//    mp3Init();
    channelsInit();
//    vTaskDelay(1000 / portTICK_RATE_MS); // Задержка перед инициализацией vuMeter Без этого валится задача
//    vuMeterInit();
    while(1){
        if(xQueueReceive(mainQ,(void *)&evt,10)) {
            ESP_LOGI(TAG, "Got Event code %d param %u",evt.code,evt.param);
            channelsEventHandler(evt.code,evt.param);
        }
        else vTaskDelay(1);
//            cmdUartSendByte(0xa5);
        time_t t = time(NULL);
        if((t - _lastKeepAlive) >= KEEPALIVE_PERIOD) {
            _lastKeepAlive = t;
//            netKeepAlive(t);
        }
    }
    
}

/*
void app_main(void){
    static time_t last;
    uint32_t level =0;
    gpio_set_direction(TEST_PIN, GPIO_MODE_DEF_OUTPUT);
    gpio_set_pull_mode(TEST_PIN, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(TEST_PIN, 0);

//    btInit();
    last = time(NULL);
    while(1){
        vTaskDelay(1);
        time_t t = time(NULL);
        if(t >= last+5) {
            last = t;
//            ESP_LOGI(TAG,"Keep alive");
            level = level ? 0 : 1;
            ESP_LOGI(TAG,"Set output %d",level);
            gpio_set_level(TEST_PIN, level);
        }
    }
}
*/
/*
void app_main(void){
    static time_t last;
    uint32_t level =0;
    gpio_set_direction(TEST_PIN, GPIO_MODE_DEF_OUTPUT);
//    gpio_set_pull_mode(TEST_PIN, GPIO_PULLUP_PULLDOWN);
    gpio_set_level(TEST_PIN, 0);
    ESP_LOGI(TAG,"Program started");
    while(1){
        level = level ? 0 : 1;
//        ESP_LOGI(TAG,"Set output %d",level);
        gpio_set_level(TEST_PIN, level);
        vTaskDelay(1);
    }
}
*/