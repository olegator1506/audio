/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include <esp_event.h>
#include <string.h>
#include <nvs_flash.h>
// Project includes
#include "common.h"
#include "i2c.h"
#include "adau17x.h"
#include "net.h"
#include "bt.h"
#include "pcf.h"

static const char *TAG="main";
extern void i2sInit(void);
extern esp_err_t pcfButtonsInit(void);
extern esp_err_t irInit(void);
QueueHandle_t mainQ;
TMainEvent evt;

void app_main(void)
{
    float left,right;
     mainQ = xQueueCreate( 50, sizeof( TMainEvent ) );
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(i2cInit());
    ESP_ERROR_CHECK(adauInit());
    ESP_ERROR_CHECK(pcfInit());
    
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(netInit());
//    ESP_ERROR_CHECK(pcfButtonsInit());
//    i2sInit();
//    btInit();
    ESP_ERROR_CHECK(irInit());
    while(1){
        if(xQueueReceive(mainQ,(void *)&evt,10)) {
            ESP_LOGI(TAG, "Got Event code %d param %u",evt.code,evt.param);
//            channelsEventHandler(evt.code,evt.param);
        } else  vTaskDelay( 1 / portTICK_PERIOD_MS);
//        adauReadLevel(&left,&right);
//        ESP_LOGI(TAG,"Level %.1f %.1f",left,right);
    }
}
/* 
void app_main(void)
{
    uint8_t bw = 0,br;
    i2cInit();
    while(1) {
        i2cWrite(CHIP_ADDRESS, &bw, 1);
        i2cRead(CHIP_ADDRESS,&br,1);
        if(bw != br)
            ESP_LOGI(TAG,"Data Error! W:%02X R:%02X",bw, br);
        vTaskDelay(1);
        bw++;
    }
}
 */