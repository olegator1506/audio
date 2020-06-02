#ifndef __IR_BUTTON_COMMNADS_H__
#define __IR_BUTTON_COMMNADS_H__
typedef struct {
    unsigned long value;
    uint8_t code;
} IrButtonCodes;


/*
    {0x0b,CMD_POWER}, 
    {0x0c,CMD_MODE},
    {0x54,CMD_PLAY_PAUSE},
    {0x48,CMD_MUTE},
// Вторая строка R G B W
    {0x41,CMD_BAND_SYS},
    {0x01,CMD_UP},
    {0x02,CMD_TITLE},
    {0x03,CMD_SUBTITLE},
    {0x4a,CMD_LEFT},
    {0x04,CMD_ENTER},
    {0x05,CMD_RIGHT},
    {0x06,CMD_SETUP},
    {0x14,CMD_STOP_REPLY},
    {0x07,CMD_DOWN},
    {0x52,CMD_VOL_PLUS},
    {0x40,CMD_VOL_MINUS},
    {0x1c,CMD_SEEK_BACK},
    {0x53,CMD_SEEK_FWD},
    {0x46,CMD_1},
    {0x19,CMD_2},
    {0x0d,CMD_3},
    {0x4b,CMD_4},
    {0x5f,CMD_5},
    {0x5b,CMD_6},
    {0x4f,CMD_7},
    {0x57,CMD_8},
    {0x5e,CMD_9},
    {0x5a,CMD_0},
    {0x4e,CMD_10},
    {0x56,CMD_GOTO},
    {0xff,CMD_NOP}
};
*/
#endif