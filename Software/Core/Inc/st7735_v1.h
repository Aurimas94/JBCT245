/* vim: set ai et ts=4 sw=4: */
#ifndef __ST7735_v1_H__
#define __ST7735_v1_H__

#include "fonts.h"
#include <stdbool.h>

#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 0
#define ST7735_YSTART 0

// call before initializing any SPI devices
void ST7735_Unselect();

void ST7735_DrawPixel_v1(uint16_t x, uint16_t y, uint16_t color);
void ST7735_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font,
		uint16_t color, uint16_t bgcolor);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t color);
void ST7735_FillScreen(uint16_t color);

void ST7735_InvertColors(bool invert);

#endif // __ST7735_v1_H__
