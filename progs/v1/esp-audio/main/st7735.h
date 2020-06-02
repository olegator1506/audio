#ifndef __ST77XX_H__
#define __ST77XX_H__
#include <stdbool.h>
#include <esp_err.h>
#include "fonts.h"

#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160



extern esp_err_t ST7735_Init(void);
extern void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
extern void ST7735_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
extern void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
extern void ST7735_FillScreen(uint16_t color);
extern void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
extern void ST7735_InvertColors(bool invert);
void ST7735_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
extern void ST7735_DrawHLine(int x1,int x2,int y,int width,int color);
extern void ST7735_DrawVLine(int y1,int y2,int x,int width,int color);
extern void ST7735_DrawLineTo(uint16_t x, int16_t y, uint16_t color);
extern void ST7735_MoveTo(uint16_t x, int16_t y);
extern void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);

#endif