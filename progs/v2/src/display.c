#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/adc.h"
#include "st7735.h"



#define DISPLY_BG_COLOR ST7735_BLACK
// константы для отображения уровня сигнала
#define CHANNEL_LEFT 0 
#define CHANNEL_RIGHT 1
#define LEVEL_LINE_WIDTH 10
#define LEVEL_YELLOW 30 // Уровень сигнала в % отображаемый желтым
#define LEVEL_RED 35 // Уровень сигнала в % отображаемый желтым
#define LEVEL_STEP_UP 100 // На сколько рисок изменяется уровень за один такт при увеличении
#define LEVEL_STEP_DOWN 100 // при уменьшении
#define LEVEL_MAX 40 // макс. значение уровня отображения
#define LEVEL_TICK_SIZE 4 // общий размер одной риски(включая пробел), при этом соблюдаем условие LEVEL_TICK_SIZE * LEVEL_MAX = SCREEN_SIZE
#define LEVEL_TICK_SPACE 1 // пробел между рисками
#define PIN_NUM_LED  27 // LED

// команды
#define DISPLAY_CMD_LEVEL 1


//static const adc_channel_t channel = ADC_CHANNEL_6;
//static const adc_atten_t atten = ADC_ATTEN_DB_0;
//static int _adcCnt = 0,_adcSum = 0;


static QueueHandle_t _cmdQ;
static const char *TAG="display";
static bool _displayState;

typedef struct {
    uint8_t cmd;
    uint16_t param1;
    uint16_t param2;
} TDisplayEvt;

static uint8_t _levelYPos[2] = {100,115};
static uint8_t _level[2] = {0,0};
static uint8_t _curLevel[2] = {0,0};


static void _convertCoordRect( int *x, int *y, int *len, int *width) {
    int retx,rety,retlen,retWidth;
    retx = *y;
    rety = ST7735_HEIGHT - *x - *len;
    retlen = *width;
    retWidth = *len;
    *x = retx;
    *y = rety;
    *len = retlen;
    *width = retWidth;
}
void displayFillRect(int x,int y,  int width, int height, int color){
    if(!_displayState) return;
    _convertCoordRect(&x,&y,width,height);
    ST7735_FillRectangle(x,y,width,height, color);
}
void displayHLine(int x, int y, int len, int width,int color) {
    if(!_displayState) return;
    _convertCoordRect(&x,&y,&len,&width);
//    ST7735_FillRectangle(y,ST7735_HEIGHT - x - len, width, len, color);
    ST7735_FillRectangle(x, y, len,width, color);
}

static void _drawTick(uint8_t ch, uint8_t pos) {
    uint16_t color;
    if(pos < LEVEL_YELLOW) color = ST7735_GREEN;
    else if(pos < LEVEL_RED) color = ST7735_YELLOW;
    else color = ST7735_RED;
    displayHLine(pos * LEVEL_TICK_SIZE, _levelYPos[ch], LEVEL_TICK_SIZE - LEVEL_TICK_SPACE, LEVEL_LINE_WIDTH,color);
}

static void _clearTick(uint8_t ch, uint8_t pos) {
    displayHLine(pos * LEVEL_TICK_SIZE, _levelYPos[ch], LEVEL_TICK_SIZE - LEVEL_TICK_SPACE, LEVEL_LINE_WIDTH,ST7735_BLACK);
}

// Отображает уровень сигнала  channel - канал Вызывается раз в 1 мс для плавного изменения положения индикатора
static void _showLevel(uint8_t ch){
    if(_curLevel[ch] == _level[ch]) return;
    if(_curLevel[ch] < _level[ch]) { // Увеличиваем уровень
        for(int i =0; i < LEVEL_STEP_UP;i++) {
            _drawTick(ch,_curLevel[ch]++);
            if(_curLevel[ch] == _level[ch]) return;
        }
    } else {
        for(int i =0; i < LEVEL_STEP_DOWN;i++) {
            _clearTick(ch,--_curLevel[ch]);
            if(_curLevel[ch] == _level[ch]) return;
        }
    }
}
/**
 * @brief Преюбразует значения в процентах в уровень отображения  индикатора уровня 
**/ 
static uint8_t _pct2Value(int value) {
    if( value < 0 ) value = 0;
    else if ( value > 100 ) value = 100;
    return value * LEVEL_MAX / 100;
}
static void _displayTask(void *pvParameters){
    TDisplayEvt event;
    int i;
    for(uint8_t i=0;i<2;i++) {
        _level[i] = 0;
        _curLevel[i] = 0;
    }
    while(1){
        if(xQueueReceive(_cmdQ, (void * )&event, 1)){
            switch(event.cmd) {
                case DISPLAY_CMD_LEVEL:
                    _level[event.param1] = _pct2Value(event.param2);
//                    ESP_LOGI(TAG,"Set level %d to %d",event.param1, _level[event.param1]);
                    break;
            }
        }
        for(i=0;i<2;i++)  _showLevel(i);
        vTaskDelay(1 / portTICK_RATE_MS);   
    }
}

void displaySetLevelPct(uint8_t ch, uint8_t level) {
    if(!_displayState) return;
    TDisplayEvt evt = {
        .cmd = DISPLAY_CMD_LEVEL,
        .param1 = ch,
        .param2 = level
    };
    xQueueSend(_cmdQ, (void *)&evt,1);
}

void displaySetLevelDb(uint8_t ch, float db){
    if(!_displayState) return;
    int res =0;
    if(db>3) res = 100;
    else if(db<=-20) res = 0;
    else res = (db+20) * 4.35;
    displaySetLevelPct(ch,res);
//    ESP_LOGI(TAG,"Db = %f Level ")
}

void displayOff(void){
    if(!_displayState) return;
    ESP_LOGI(TAG,"Display OFF");
    ST7735_FillScreen(ST7735_BLACK);
    gpio_set_level(PIN_NUM_LED, 0);
    _displayState = false;
    ST7735_WriteString(2,2,"Standby",Font_11x18,ST7735_BLACK,ST7735_BLUE);
}

void displayOn(void){
    if(_displayState) return;
    ESP_LOGI(TAG,"Display ON");
    ST7735_FillScreen(ST7735_BLACK);
    gpio_set_level(PIN_NUM_LED, 1);
    _displayState = true;
}




void displayInit(void) {
    gpio_set_direction(PIN_NUM_LED, GPIO_MODE_DEF_OUTPUT);
    gpio_set_level(PIN_NUM_LED, 1);
    ESP_ERROR_CHECK(ST7735_Init());
        //Initialize the LCD
    _cmdQ = xQueueCreate( 20, sizeof( TDisplayEvt));
    xTaskCreate(_displayTask, "display_task",2048,NULL,12,NULL);
    _displayState = false;
    displayOn();
}

