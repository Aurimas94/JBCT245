/* vim: set ai et ts=4 sw=4: */
#include "main.h"
#include "st7735_v1.h"
#include "st7735.h"
extern SPI_HandleTypeDef hspi1;

static void
ST7735_Select ()
{
  CS_LOW
  ;
}

void
ST7735_Unselect ()
{
  CS_HIGH
  ;
}

static void
ST7735_WriteCommand (uint8_t cmd)
{
  DC_LOW
  ;
  HAL_SPI_Transmit (&hspi1, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

static void
ST7735_WriteData (uint8_t *buff, size_t buff_size)
{
  DC_HIGH
  ;
  HAL_SPI_Transmit (&hspi1, buff, buff_size, HAL_MAX_DELAY);
}

static void
ST7735_SetAddressWindow (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  // column address set
  ST7735_WriteCommand (ST7735_CASET);
  uint8_t data[] =
    { 0x00, x0 + ST7735_XSTART, 0x00, x1 + ST7735_XSTART };
  ST7735_WriteData (data, sizeof(data));

  // row address set
  ST7735_WriteCommand (ST7735_RASET);
  data[1] = y0 + ST7735_YSTART;
  data[3] = y1 + ST7735_YSTART;
  ST7735_WriteData (data, sizeof(data));

  // write to RAM
  ST7735_WriteCommand (ST7735_RAMWR);
}

void
ST7735_DrawPixel_v1 (uint16_t x, uint16_t y, uint16_t color)
{
  if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
    return;

  ST7735_Select ();

  ST7735_SetAddressWindow (x, y, x + 1, y + 1);
  uint8_t data[] =
    { color >> 8, color & 0xFF };
  ST7735_WriteData (data, sizeof(data));

  ST7735_Unselect ();
}

static void
ST7735_WriteChar (uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color,
		  uint16_t bgcolor)
{
  uint32_t i, b, j;

  ST7735_SetAddressWindow (x, y, x + font.width - 1, y + font.height - 1);

  for (i = 0; i < font.height; i++)
    {
      b = font.data[(ch - 32) * font.height + i];
      for (j = 0; j < font.width; j++)
	{
	  if ((b << j) & 0x8000)
	    {
	      uint8_t data[] =
		{ (color >> 8) & 0xFF, color & 0xFF };
	      ST7735_WriteData (data, sizeof(data));
	    }
	  else
	    {
	      uint8_t data[] =
		{ (bgcolor >> 8) & 0xFF, bgcolor & 0xFF };
	      ST7735_WriteData (data, sizeof(data));
	    }
	}
    }
}

/*
 Simpler (and probably slower) implementation:

 static void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color) {
 uint32_t i, b, j;

 for(i = 0; i < font.height; i++) {
 b = font.data[(ch - 32) * font.height + i];
 for(j = 0; j < font.width; j++) {
 if((b << j) & 0x8000)  {
 ST7735_DrawPixel(x + j, y + i, color);
 }
 }
 }
 }
 */

void
ST7735_WriteString (uint16_t x, uint16_t y, const char *str, FontDef font,
		    uint16_t color, uint16_t bgcolor)
{
  ST7735_Select ();

  while (*str)
    {
      if (x + font.width >= ST7735_WIDTH)
	{
	  x = 0;
	  y += font.height;
	  if (y + font.height >= ST7735_HEIGHT)
	    {
	      break;
	    }

	  if (*str == ' ')
	    {
	      // skip spaces in the beginning of the new line
	      str++;
	      continue;
	    }
	}

      ST7735_WriteChar (x, y, *str, font, color, bgcolor);
      x += font.width;
      str++;
    }

  ST7735_Unselect ();
}

void
ST7735_FillRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		      uint16_t color)
{
  // clipping
  if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
    return;
  if ((x + w - 1) >= ST7735_WIDTH)
    w = ST7735_WIDTH - x;
  if ((y + h - 1) >= ST7735_HEIGHT)
    h = ST7735_HEIGHT - y;

  ST7735_Select ();
  ST7735_SetAddressWindow (x, y, x + w - 1, y + h - 1);

  uint8_t data[] =
    { color >> 8, color & 0xFF };
  DC_HIGH
  ;
  for (y = h; y > 0; y--)
    {
      for (x = w; x > 0; x--)
	{
	  HAL_SPI_Transmit (&hspi1, data, sizeof(data),
	  HAL_MAX_DELAY);
	}
    }

  ST7735_Unselect ();
}

void
ST7735_FillScreen (uint16_t color)
{
  ST7735_FillRectangle (0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void
ST7735_InvertColors (bool invert)
{
  ST7735_Select ();
  ST7735_WriteCommand (invert ? ST7735_INVON : ST7735_INVOFF);
  ST7735_Unselect ();
}

