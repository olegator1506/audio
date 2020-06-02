/**
 * Программа управления модулем МР3 через UART
 * Команды принимаются функцией mp3Cmd и ставятся в очередь _mp3CmdQ
 * В основоной задаче очередь опрашивается (ф-я cmdEventLoop) и если порт свободен команда передается в модуль
 * В очередь _mp3UartQ помещаются события UART, по событию приема данных вызывается ф-я _mp3UartExecReceive
 * в котоой проверяются данные, снимается флаг занятости порта, генерится соответствующее событие в основную очередь mainQ
 * (через функцию _mp3SendEvent)
 **/

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
#include "mp3.h"



#define MP3_TXD_PIN  (GPIO_NUM_4)
#define MP3_RXD_PIN  (GPIO_NUM_5)
#define MP3_RTS_PIN  (UART_PIN_NO_CHANGE)
#define MP3_CTS_PIN  (UART_PIN_NO_CHANGE)

#define MP3_UART_NUM UART_NUM_1
#define MP3_BUF_SIZE 128
#define MP3_ANSWER_TIMEOUT 3000000l

typedef struct {
    uint8_t code;
    uint16_t param;
    uint16_t delay;
    bool feedback;
} TUartCmdEvt;



#define MP3_CMD_RESET 0x0c

static uint8_t _sendBuf[10];
static QueueHandle_t _mp3UartQ,_mp3CmdQ;
static const char *TAG="mp3";
static uint8_t _mp3Answer[10];
static bool _mp3AnswerReady = false;
static bool _portBusy = false; 
static uint64_t _lastCmdTime;

TMp3State _mp3State;

/**
**/
void _mp3SendEvent(uint8_t code, uint16_t param){
    TMainEvent evt;
    evt.code = code;
    evt.param = param;
    xQueueSend(mainQ, (void *)&evt,10);
}

bool _waitAnswer(int waitTimeout){
    for(int i=0;i<waitTimeout;i++) {
        if(_mp3AnswerReady) {
            _mp3State.connected = true;    
            return true;
        }    
        else    vTaskDelay(1);
    }
    return false;
}



void _sendCmd(uint8_t cmd, uint16_t param,bool feedback)
{
    ESP_LOGI(TAG,"Send cmd %02X param %u feedback %s",cmd,param, feedback ? "yes":"no");
    _sendBuf[0] = 0x7e;// start byte
    _sendBuf[1] = 0xff;//version
    _sendBuf[2] = 6;//length 
    _sendBuf[3] = cmd;// command code
    _sendBuf[4] = feedback ? 1:0;// feedback
    _sendBuf[5] = (param >> 8) & 0xff;// param MSB
    _sendBuf[6] = param & 0xff;// param LSB
    _sendBuf[7] = 0xef;// finish byte
    _mp3AnswerReady = false;
    uart_write_bytes(MP3_UART_NUM, (const char *) _sendBuf, 8);
    _portBusy = true;
    _lastCmdTime = esp_timer_get_time();
}

/**
 * @summary формирует строку отображения принятого пакета
**/
char *_responseStr(uint8_t *data, int len){
    static char *s = NULL;
    if(s != NULL) free(s);
    s = (char *)malloc(len*3 + 1);
    for(int i=0; i<len;i++)  sprintf(s+(i*3),"%02X ",data[i]);
    s[len*3] = '\0';
    return s;   
}


void _mp3ExecResponse(uint8_t *dtmp) {
    uint16_t evtParam;
    for(int i=0;i<10;i++) _mp3Answer[i] = dtmp[i];
    ESP_LOGI(TAG,"Got answer %s",_responseStr(dtmp,10));
    _mp3AnswerReady = true;
    switch(_mp3Answer[3]) {
        case 0x3f: // Init answer
            if(_mp3Answer[6] & 1)_mp3State.usbPlugged = true;
            if(_mp3Answer[6] & 2)_mp3State.sdPlugged = true;
            if(_mp3Answer[6] & 4)_mp3State.pcPlugged = true;
            _mp3SendEvent(MY_EVENT_MP3_CONNECT,_mp3Answer[6]);
            break;
        case 0x3c: // USB track finished
            _mp3SendEvent(MY_EVENT_MP3_PLAY_TRACK_FINISH,_mp3Answer[6]);
            break;     
        case 0x3d: // SD track finished
            _mp3SendEvent(MY_EVENT_MP3_PLAY_TRACK_FINISH,_mp3Answer[6]);
            
            break;     
        case 0x41: // Feedback
            break;    
        case 0x40:// error 
            evtParam = _mp3Answer[6];
            _mp3SendEvent(MY_EVENT_MP3_ERROR,evtParam);
            _mp3State.errCode = _mp3Answer[6];
            break;
        case 0x3a:// media plugged in
            evtParam = _mp3Answer[6];
            _mp3SendEvent(MY_EVENT_MP3_MEDIA_PLUGIN,evtParam);
            switch(_mp3Answer[6]) {
                case 1: _mp3State.usbPlugged = true;break;
                case 2: _mp3State.sdPlugged = true;break;
                case 4: _mp3State.pcPlugged = true;break;
            }
            break;
        case 0x3b:// media plugged out
            evtParam = _mp3Answer[6];
            _mp3SendEvent(MY_EVENT_MP3_MEDIA_PLUGOUT,evtParam);
            switch(_mp3Answer[6]) {
                case 1: _mp3State.usbPlugged = false;break;
                case 2: _mp3State.sdPlugged = false;break;
                case 4: _mp3State.pcPlugged = false;break;
            }
            break;
        // Total files response
        case 0x47:
        case 0x48:
            _mp3SendEvent((_mp3Answer[3] == 0x47) ? MY_EVENT_MP3_USB_TOTAL_FILES : MY_EVENT_MP3_SD_TOTAL_FILES,(_mp3Answer[5] << 8) + _mp3Answer[6]);
            break;
        case 0x4f:// Total folders on media
            _mp3SendEvent(MY_EVENT_MP3_TOTAL_FOLDERS,(_mp3Answer[5] << 8) + _mp3Answer[6]);
            break;
        case 0x4e:// Total track in a folder
            _mp3SendEvent(MY_EVENT_MP3_TOTAL_TRACKS,(_mp3Answer[5] << 8) + _mp3Answer[6]);
            break;
    }
}

/**
 * @summary Вызывается по событию приема данных UART
 * @param len размер принятого блока данных
**/
void _mp3UartExecReceive(size_t len){
    uint8_t dtmp[10];
    if(len < 10) {
        uart_read_bytes(MP3_UART_NUM, dtmp, len, portMAX_DELAY);
        return;    
    }
    while(len >=10) {
        uart_read_bytes(MP3_UART_NUM, dtmp, 10, portMAX_DELAY); 
        _mp3ExecResponse(dtmp);
        len -=10;   
    }
    if(len > 0) {
        for(int i=0;i<len;i++) uart_read_bytes(MP3_UART_NUM, dtmp, 1, portMAX_DELAY);
    }
    _portBusy = false;
}


void _uartEventLoop(void) {
    uart_event_t event;
    uint8_t* dtmp = (uint8_t*) malloc(MP3_BUF_SIZE);

        if(xQueueReceive(_mp3UartQ, (void * )&event, 1)) {
            bzero(dtmp, MP3_BUF_SIZE);
            ESP_LOGI(TAG, "uart[%d] event:", MP3_UART_NUM);
            switch(event.type) {
                case UART_DATA:
                    ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                    _mp3UartExecReceive(event.size);
                    ESP_LOGI(TAG, "[DATA EVT]:");
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(MP3_UART_NUM);
                    xQueueReset(_mp3UartQ);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    // If buffer full happened, you should consider encreasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(MP3_UART_NUM);
                    xQueueReset(_mp3UartQ);
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
/*
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(MP3_UART_NUM, &buffered_size);
                    int pos = uart_pattern_pop_pos(EX_UART_NUM);
                    ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                        // record the position. We should set a larger queue size.
                        // As an example, we directly flush the rx buffer here.
                        uart_flush_input(MP3_UART_NUM);
                    } else {
                        uart_read_bytes(MP3_UART_NUM, dtmp, pos, 100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_CHR_NUM + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(EX_UART_NUM, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                        ESP_LOGI(TAG, "read data: %s", dtmp);
                        ESP_LOGI(TAG, "read pat : %s", pat);
                    }
                    break;
*/
                //Others
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
        free(dtmp);
        dtmp = NULL;
}

static void _cmdEventLoop(void){
    TUartCmdEvt event;
    if(_portBusy) {
        // если устройство не отвечает по истечении таймаута
        if((esp_timer_get_time() - _lastCmdTime) > MP3_ANSWER_TIMEOUT) { 
             _portBusy = false;
// Считаем это ошибкой или считаем что модуль отключился (закоментарь ненужное)            
//            _mp3SendEvent(MY_EVENT_MP3_ERROR,0x10); _mp3State.errCode = 0x10;
            _mp3SendEvent(MY_EVENT_MP3_DISCONNECT,0); _mp3State.connected = false;
        }
        return;
    }
    if(xQueueReceive(_mp3CmdQ, (void * )&event, 1)){
        _sendCmd(event.code,event.param,event.feedback);
        for(int i = 0; i< event.delay;i++) 
            _uartEventLoop();
    }
}



static void _mp3Task(void *pvParameters){
    ESP_LOGI(TAG, "Task started");
    for(;;){
        _uartEventLoop();
        _cmdEventLoop();
    }
    vTaskDelete(NULL);
}

static bool _reset(){
        _mp3State.connected = false;
        _mp3State.sdPlugged = false;
        _mp3State.usbPlugged = false;
        _mp3State.pcPlugged =false;
        _mp3State.errCode = 0;
        _mp3State.playing = false;
    uart_flush(MP3_UART_NUM);
    _sendCmd(MP3_CMD_RESET,0,false);
    if(_waitAnswer(20000)) {
        return true;
    }
    return false;
}

void mp3Init(void) {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_delete(MP3_UART_NUM);
    ESP_ERROR_CHECK(uart_param_config(MP3_UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(MP3_UART_NUM, MP3_TXD_PIN, MP3_RXD_PIN, MP3_RTS_PIN, MP3_CTS_PIN));
    const int bufLen = MP3_BUF_SIZE *2;
    ESP_ERROR_CHECK(uart_driver_install(MP3_UART_NUM,bufLen,bufLen,10,&_mp3UartQ,0));
    _mp3CmdQ = xQueueCreate( 20, sizeof( TUartCmdEvt ) );
    uart_enable_rx_intr(MP3_UART_NUM);
    xTaskCreate(_mp3Task, "mp3_task",2048,NULL,12,NULL);
    _reset();
}
/**
 * @summary Добавляет команду в очередь 
 * @param cmd код команды
 * @param param 16-и битный параметр передаваемый модулю
 * @param delay - задержка в мс выполняемая после передачи команды
 * @param feedback - признак необходимости возврата ответа, данный признак должен устанавливаться для всех команд в которых не подразумевается ответ модуля
 * 
**/ 
void mp3Cmd(uint8_t code, uint16_t param, uint16_t delay,bool feedback) {
    TUartCmdEvt evt = {
        .code =  code,
        .param = param,
        .delay = delay,
        .feedback = feedback
    };
    xQueueSend(_mp3CmdQ, (void *)&evt,10);
}

/**
 * Возвращает указатель на структуру _mp3State
**/ 
TMp3State* mp3GetState(void){
    return &_mp3State;
}


void mp3Play(uint8_t trackNum){
    ESP_LOGI(TAG,"Play track #%d",trackNum);
    _sendCmd(3,trackNum,true);
}



void mp3MediaSelect(uint8_t mediaNum){
    ESP_LOGI(TAG,"Select media # %u",mediaNum);
    mp3Cmd(0x09,mediaNum,0,true);
}

