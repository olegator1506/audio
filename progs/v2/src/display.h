#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "esp_err.h"

extern void displayInit(void);
extern void displayHLine(int x, int y, int len, int width,int color);
extern void displaySetLevelPct(uint8_t channel, uint8_t level);
extern void displaySetLevelDb(uint8_t ch, float db);
extern void displayFillRect(int x,int y,  int width, int height, int color);
extern void displayOff(void);
extern void displayOn(void);
#endif