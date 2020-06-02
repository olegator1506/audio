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
#include <esp_log.h>
#include <string.h>
#include "nvs_flash.h"
// Project includes
#include "i2c.h"
#include "adau17x.h"
#include "net.h"

static const char *TAG="main";


void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(i2cInit());
    ESP_ERROR_CHECK(adauInit());
    ESP_ERROR_CHECK(netInit());
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