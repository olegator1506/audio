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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h" 
#include "freertos/queue.h"
#include <esp_event.h>
#include <esp_log.h>
#include <string.h>
#include "nvs_flash.h"
// Project includes
#include "mp3.h"
#include "common.h"
#include "config.h"

static const char *TAG="main";
QueueHandle_t mainQ;
TMainEvent evt;
TMp3State* mp3State;
static time_t _lastKeepAlive = 0;

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    mainQ = xQueueCreate( 50, sizeof( TMainEvent ) );
    mp3Init(MP3_TXD_PIN,MP3_RXD_PIN);
    ESP_LOGI(TAG,"Program started");
    while(1){
        if(xQueueReceive(mainQ,(void *)&evt,10)) {
            ESP_LOGI(TAG, "Got Event code %d param %u",evt.code,evt.param);
            switch(evt.code) {
                case MY_EVENT_MP3_CONNECT:
//                    if(evt.param & 0x01) mp3ReadMedia(1);
                    break;
            }
        }
        else vTaskDelay(1);
//            cmdUartSendByte(0xa5);
        time_t t = time(NULL);
        if((t - _lastKeepAlive) >= KEEPALIVE_PERIOD) {
            _lastKeepAlive = t;
//            netKeepAlive(t);
            ESP_LOGI(TAG,"Keep alive");
        }
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