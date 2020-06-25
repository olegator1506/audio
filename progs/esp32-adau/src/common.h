#ifndef _COMMON_H_
#define _COMMON_H_
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#define     MY_EVENT_MP3_CONNECT 1
#define     MY_EVENT_MP3_DISCONNECT 2
#define     MY_EVENT_MP3_MEDIA_PLUGIN 3
#define     MY_EVENT_MP3_MEDIA_PLUGOUT 4
#define     MY_EVENT_MP3_ERROR 5
#define     MY_EVENT_MP3_PLAY_TRACK_FINISH 6
#define     MY_EVENT_MP3_USB_TOTAL_FILES 7
#define     MY_EVENT_MP3_SD_TOTAL_FILES 8
#define     MY_EVENT_MP3_TOTAL_FOLDERS 9
#define     MY_EVENT_MP3_TOTAL_TRACKS 10
#define     MY_EVENT_CONTROL_CMD 11
#define     MY_EVENT_BT_STATE 12
#define     MY_EVENT_BT_ATTR 13
#define     MY_EVENT_BUTTON_PRESSED 14
#define     MY_EVENT_BUTTON_RELEASED 15

#define KEEPALIVE_PERIOD 60

typedef enum {
    PLAYER_STATE_NOT_SUPPORT,
    PLAYER_STATE_STOP,
    PLAYER_STATE_PAUSE,
    PLAYER_STATE_PLAY
} TPlayerState;

typedef struct {
    uint8_t code;
    uint16_t param;
} TMainEvent;

extern QueueHandle_t mainQ;
#endif