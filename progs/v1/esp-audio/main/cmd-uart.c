#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "esp_log.h"
#include "common.h"


#define CMD_UART_TXD_PIN  (GPIO_NUM_33)
#define CMD_UART_RXD_PIN  (GPIO_NUM_36)
#define CMD_UART_RTS_PIN  (UART_PIN_NO_CHANGE)
#define CMD_UART_CTS_PIN  (UART_PIN_NO_CHANGE)
#define CMD_UART_NUM UART_NUM_2
#define CMD_BUF_SIZE 128
#define CMD_PING_TIMEOUT 2000

static QueueHandle_t _cmdUartQ;
static const char *TAG="cmd_uart";
static bool _pingAnswered = false;
extern QueueHandle_t mainQ;


// Вызывается по приему данных. Выполняет чтение данных из буфера приема и генерацию события в очередь mainQ
static void _cmdExec(int len){
    uint8_t b;
    TMainEvent evt;
    evt.code = MY_EVENT_CONTROL_CMD;
    for(int i=0;i<len;i++) {
        uart_read_bytes(CMD_UART_NUM, &b, 1, portMAX_DELAY) ;
        evt.param = b;
        ESP_LOGI(TAG,"Got byte %02x",b);
        if(b == 0x10) _pingAnswered = true;
        xQueueSend(mainQ, (void *)&evt,10);
    }
}



static void _uartEventLoop(void) {
    uart_event_t event;
        if(xQueueReceive(_cmdUartQ, (void * )&event, 1)) {
            ESP_LOGI(TAG, "uart[%d] event:", CMD_UART_NUM);
            switch(event.type) {
                case UART_DATA:
                    ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                    _cmdExec(event.size);
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(CMD_UART_NUM);
                    xQueueReset(_cmdUartQ);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(CMD_UART_NUM);
                    xQueueReset(_cmdUartQ);
                    break;
                //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
}

static bool _ping(void){
    uint8_t b = 0x10;
    _pingAnswered = false;
    for(int i =0;i < CMD_PING_TIMEOUT;i++) {
        uart_write_bytes(CMD_UART_NUM, (const char *)&b, 1); 
        _uartEventLoop();
        if(_pingAnswered) {
            ESP_LOGI(TAG,"Arduino ping Ok on retry %d",i);
            return true;
        }   
    }
    ESP_LOGI(TAG,"No answer from Arduino");
    return;
}

static void _cmdUartTask(void *pvParameters){
    ESP_LOGI(TAG, "Task started");
    _ping();
    for(;;){
        _uartEventLoop();
    }
    vTaskDelete(NULL);
}

void cmdUartSendByte(uint8_t data) {
    ESP_LOGI(TAG,"Send byte %02X",data);
    uart_write_bytes(CMD_UART_NUM, (const char *)&data, 1);
}

void cmdUartInit(void) {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_delete(CMD_UART_NUM);
    ESP_ERROR_CHECK(uart_param_config(CMD_UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(CMD_UART_NUM, CMD_UART_TXD_PIN, CMD_UART_RXD_PIN, CMD_UART_RTS_PIN, CMD_UART_CTS_PIN));
    const int bufLen = CMD_BUF_SIZE *2;
    _cmdUartQ = xQueueCreate( 20, 1 );
    ESP_ERROR_CHECK(uart_driver_install(CMD_UART_NUM,bufLen,bufLen,10,&_cmdUartQ,0));
    uart_enable_rx_intr(CMD_UART_NUM);
    xTaskCreate(_cmdUartTask, "cmd_uart_task",2048,NULL,12,NULL);
}
