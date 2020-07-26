/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
//#define UNIT_TEST
#ifndef UNIT_TEST
#include "config.h"
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
#include "pcf.h"
#include "channel.h"
#include "bt.h"
#include "i2s.h"

static const char *TAG="main";
extern esp_err_t irInit(uint16_t address, int pin);
QueueHandle_t mainQ;
TMainEvent evt;

void app_main(void)
{
//    float left,right;
     mainQ = xQueueCreate( 50, sizeof( TMainEvent ) );
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(i2cInit( I2C_PORT_NUM, I2C_SDA_PIN, I2C_SCL_PIN,I2C_FR,I2C_TIMEOUT));
    ESP_ERROR_CHECK(adauInit(I2C_ADDRESS_ADAU));
    ESP_ERROR_CHECK(pcfInit());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(netInit());
    i2sInit(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
    btInit(BT_DEV_NAME);
//    ESP_ERROR_CHECK(irInit(IR_RMT_ADDRESS, IR_RMT_PIN));
//    ESP_ERROR_CHECK(channelsInit());
    pcfSelAnalogInput(1);
    while(1){
        if(xQueueReceive(mainQ,(void *)&evt,10)) {
            ESP_LOGI(TAG, "Got Event code %d param %u",evt.code,evt.param);
//            channelsEventHandler(evt.code,evt.param);
        } else  vTaskDelay( 1 / portTICK_PERIOD_MS);
//        adauReadLevel(&left,&right);
//        ESP_LOGI(TAG,"Level %.1f %.1f",left,right);
    }
}
#else // Testing mode

#include <stdio.h>
#include <esp_log.h>
#include <string.h>
#include <nvs_flash.h>
// Project includes
#include <unity.h>
#include "config.h"
#include "i2c.h"
#include "pcf.h"
#include "adau17x.h"




static const char *TAG="main";

void testI2cWriteRead()
{
    uint8_t pcfWrByte = 0,pcfRdByte = 0;
    for( int i=0;i<256;i++){
        pcfWrByte = i & 0xff;
        TEST_ASSERT(i2cWrite(I2C_ADDRESS_CH_SWITCH,&pcfWrByte,1) == ESP_OK);
        TEST_ASSERT(i2cRead(I2C_ADDRESS_CH_SWITCH,&pcfRdByte,1) == ESP_OK);
        TEST_ASSERT(pcfRdByte == pcfWrByte);
    } 
}
void testPcfSetAnalogInput(){
    uint8_t b;
    for(uint8_t i = 0; i<4; i++){
        TEST_ASSERT(pcfSelAnalogInput(i) == ESP_OK);
        TEST_ASSERT(i2cRead(I2C_ADDRESS_CH_SWITCH,&b,1) == ESP_OK);
        ESP_LOGI(TAG,"Set channel %d Read byte %02X",i,b);
        TEST_ASSERT(((b >>6) & 0x03)== i);
    }
}
void testAdau(){
    adauSetChipAddress(I2C_ADDRESS_ADAU);
    TEST_ASSERT(adauLoadProgram() == ESP_OK);
//    TEST_ASSERT(adauI2sOn() == ESP_OK);
//    TEST_ASSERT(adauI2sOff() == ESP_OK);
}
void app_main(void)
{

    UNITY_BEGIN();
    TEST_ASSERT(i2cInit(I2C_PORT_NUM, I2C_SDA_PIN, I2C_SCL_PIN,I2C_FR,I2C_TIMEOUT) == ESP_OK);
    RUN_TEST(testI2cWriteRead);
    TEST_ASSERT(pcfInit() == ESP_OK);
    RUN_TEST(testPcfSetAnalogInput);
    RUN_TEST(testAdau);
    UNITY_END();
}

#endif // UNIT_TEST