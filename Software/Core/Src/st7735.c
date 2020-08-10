#include "st7735.h"

extern SPI_HandleTypeDef hspi1;

void ST7735_write(uint8_t data) {
	HAL_SPI_Transmit(&hspi1, &data, sizeof(data), HAL_MAX_DELAY);
}
void ST7735_Send(uint8_t data) {
	HAL_SPI_Transmit(&hspi1, &data, sizeof(data), HAL_MAX_DELAY);
}

void ST7735_SendData(uint8_t data) {
	DC_HIGH
	;
	ST7735_write(data);
}

void ST7735_SendCmd(uint8_t cmd) {
	DC_LOW
	;
	ST7735_write(cmd);
}

void ST7735_Init(void) {

	CS_HIGH
	;
	RESET_HIGH
	;
	HAL_Delay(5);
	RESET_LOW
	;
	HAL_Delay(5);
	RESET_HIGH
	;

	CS_LOW
	;

	ST7735_SendCmd(ST7735_SWRESET);
	HAL_Delay(150);

	ST7735_SendCmd(ST7735_SLPOUT);
	HAL_Delay(500);

	ST7735_SendCmd(ST7735_FRMCTR1);
	ST7735_SendData(0x01);
	ST7735_SendData(0x2C);
	ST7735_SendData(0x2D);

	ST7735_SendCmd(ST7735_FRMCTR2);
	ST7735_SendData(0x01);
	ST7735_SendData(0x2C);
	ST7735_SendData(0x2D);

	ST7735_SendCmd(ST7735_FRMCTR3);
	ST7735_SendData(0x01);
	ST7735_SendData(0x2C);
	ST7735_SendData(0x2D);
	ST7735_SendData(0x01);
	ST7735_SendData(0x2C);
	ST7735_SendData(0x2D);

	ST7735_SendCmd(ST7735_INVCTR);
	ST7735_SendData(0x07); //07

	ST7735_SendCmd(ST7735_PWCTR1);
	ST7735_SendData(0xA2);
	ST7735_SendData(0x02);
	ST7735_SendData(0x84);

	ST7735_SendCmd(ST7735_PWCTR2);
	ST7735_SendData(0xC5);

	ST7735_SendCmd(ST7735_PWCTR3);
	ST7735_SendData(0x0A);
	ST7735_SendData(0x00);

	ST7735_SendCmd(ST7735_PWCTR4);
	ST7735_SendData(0x8A);
	ST7735_SendData(0x2A);

	ST7735_SendCmd(ST7735_PWCTR5);
	ST7735_SendData(0x8A);
	ST7735_SendData(0xEE);

	ST7735_SendCmd(ST7735_VMCTR1);
	ST7735_SendData(0x0E);

	ST7735_SendCmd(ST7735_INVOFF);
	//ST7735_SendCmd(ST7735_INVON);

	//ST7735_SendCmd(ST7735_MADCTL);
	//ST7735_SendData(0xFC); //c8

	ST7735_SendCmd(ST7735_COLMOD);
	ST7735_SendData(0x05);

	ST7735_SendCmd(ST7735_CASET);
	ST7735_SendData(0x00);
	ST7735_SendData(0x00);
	ST7735_SendData(0x00);
	ST7735_SendData(0x7F);	//7F

	ST7735_SendCmd(ST7735_RASET);
	ST7735_SendData(0x00);
	ST7735_SendData(0x00);
	ST7735_SendData(0x00);
	ST7735_SendData(0x9F);	//9F//7F

	ST7735_SendCmd(ST7735_GMCTRP1);
	ST7735_SendData(0x02);
	ST7735_SendData(0x1c);
	ST7735_SendData(0x07);
	ST7735_SendData(0x12);
	ST7735_SendData(0x37);
	ST7735_SendData(0x32);
	ST7735_SendData(0x29);
	ST7735_SendData(0x2d);
	ST7735_SendData(0x29);
	ST7735_SendData(0x25);
	ST7735_SendData(0x2B);
	ST7735_SendData(0x39);
	ST7735_SendData(0x00);
	ST7735_SendData(0x01);
	ST7735_SendData(0x03);
	ST7735_SendData(0x10);

	ST7735_SendCmd(ST7735_GMCTRN1);
	ST7735_SendData(0x03);
	ST7735_SendData(0x1d);
	ST7735_SendData(0x07);
	ST7735_SendData(0x06);
	ST7735_SendData(0x2E);
	ST7735_SendData(0x2C);
	ST7735_SendData(0x29);
	ST7735_SendData(0x2D);
	ST7735_SendData(0x2E);
	ST7735_SendData(0x2E);
	ST7735_SendData(0x37);
	ST7735_SendData(0x3F);
	ST7735_SendData(0x00);
	ST7735_SendData(0x00);
	ST7735_SendData(0x02);
	ST7735_SendData(0x10);

	ST7735_SendCmd(ST7735_NORON);
	HAL_Delay(10);

	ST7735_SendCmd(ST7735_DISPON);
	HAL_Delay(100);

	ST7735_SendCmd(ST7735_MADCTL);
	ST7735_SendData(0xA8); //c8

	ST7735_Clear(ST7735_BLACK);

}

void ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE) {
	ST7735_SendCmd(ST7735_CASET); // Column address set
	DC_HIGH
	;
	ST7735_Send(0x00);
	ST7735_Send(XS);
	ST7735_Send(0x00);
	ST7735_Send(XE);

	ST7735_SendCmd(ST7735_RASET); // Row address set
	DC_HIGH
	;
	ST7735_Send(0x00);
	ST7735_Send(YS);
	ST7735_Send(0x00);
	ST7735_Send(YE);

	ST7735_SendCmd(ST7735_RAMWR); // Memory write
}

void ST7735_Clear(uint16_t Color) {
	uint16_t i;
	uint8_t CL, CH;
	CL = Color & 0xFF;
	CH = (Color >> 8) & 0xFF;
	//ST7735_AddrSet(0,0,128,160);//
	ST7735_AddrSet(0, 0, 160, 128); //
	DC_HIGH
	;
	for (i = 0; i < 20480; i++) {
		ST7735_Send(CH);
		ST7735_Send(CL);
	}
}

void ST7735_DrawPixel(uint8_t x, uint8_t y, uint16_t Color) {
	uint8_t CL, CH;
	CL = Color & 0xFF;
	CH = (Color >> 8) & 0xFF;
	ST7735_AddrSet(x, y, x + 1, y + 1);
	DC_HIGH
	;
	ST7735_Send(CH);
	ST7735_Send(CL);
}

void ST7735_DrawHLine(uint8_t x, uint8_t x1, uint8_t y, uint16_t Color) {
	uint16_t i, len;
	uint8_t CL, CH;
	CL = Color & 0xFF;
	CH = (Color >> 8) & 0xFF;
	ST7735_AddrSet(x, y, x1, y);
	len = x1 - x;
	DC_HIGH
	;
	for (i = 0; i < len; i++) {
		ST7735_Send(CH);
		ST7735_Send(CL);
	}
}

void ST7735_DrawVLine(uint8_t x, uint8_t y, uint8_t y1, uint16_t Color) {
	uint16_t i, len;
	uint8_t CL, CH;
	CL = Color & 0xFF;
	CH = (Color >> 8) & 0xFF;
	ST7735_AddrSet(x, y, x, y1);
	len = y1 - y;
	DC_HIGH
	;
	for (i = 0; i < len; i++) {
		ST7735_Send(CH);
		ST7735_Send(CL);
	}
}

void ST7735_DrawBMP(const uint8_t *array, uint32_t length) {
	uint16_t i;
	ST7735_AddrSet(0, 0, 128, 160);
	DC_HIGH
	;
	for (i = 0; i < length; i++) {
		ST7735_Send(array[i]);
	}
}

void ST7735_DrawChar5x7(uint8_t x, uint8_t y, uint8_t chr, uint16_t color,
		uint16_t background_color) {
	uint8_t i, j;
	uint8_t CH, CL, BCH, BCL;
	uint8_t buffer[5];

	CL = color & 0xFF;
	CH = (color >> 8) & 0xFF;

	BCL = background_color & 0xFF;
	BCH = (background_color >> 8) & 0xFF;

	memcpy(buffer, &Font5x7[(chr - 32) * 5], 5);
	ST7735_AddrSet(x, y, x + 5, y + 7);

	DC_HIGH
	;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 5; j++) {
			if ((buffer[j] & (1 << i)) == 0) {
				ST7735_Send(BCH);
				ST7735_Send(BCL);
			} else {
				ST7735_Send(CH);
				ST7735_Send(CL);
			}
		}
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
	for (i = 0; i < 5; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
}

void ST7735_DrawChar7x11(uint8_t x, uint8_t y, uint8_t chr, uint16_t color,
		uint16_t background_color) {
	uint8_t i, j;
	uint8_t CH, CL, BCH, BCL;
	uint8_t buffer[11];

	CL = color & 0xFF;
	CH = (color >> 8) & 0xFF;

	BCL = background_color & 0xFF;
	BCH = (background_color >> 8) & 0xFF;

	memcpy(buffer, &Font7x11[(chr - 32) * 11], 11);
	ST7735_AddrSet(x, y, x + 7, y + 11);
	DC_HIGH
	;
	for (j = 0; j < 11; j++) {
		for (i = 0; i < 7; i++) {
			if ((buffer[j] & (1 << i)) == 0) {
				ST7735_Send(BCH);
				ST7735_Send(BCL);
			} else {
				ST7735_Send(CH);
				ST7735_Send(CL);
			}
		}
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
	for (i = 0; i < 7; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
}

void ST7735_DrawString7x11(uint8_t x, uint8_t y, uint8_t *chr, uint16_t color,
		uint16_t background_color) {
	uint8_t i = 0;
	while (chr[i] != '\0') {
		ST7735_DrawChar7x11(x + (7 * i), y, chr[i], color, background_color);
		i++;
	}
}
void ST7735_DrawString5x7(uint8_t x, uint8_t y, uint8_t *chr, uint16_t color,
		uint16_t background_color) {
	uint8_t i = 0;
	while (chr[i] != '\0') {
		ST7735_DrawChar5x7(x + (5 * i), y, chr[i], color, background_color);
		i++;
	}
}

void ST7735_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
		uint16_t Color) {
	ST7735_DrawHLine(x, x + w, y, Color);
	ST7735_DrawVLine(x + w, y, y + h + 1, Color);
	ST7735_DrawHLine(x, x + w, y + h, Color);
	ST7735_DrawVLine(x, y, y + h, Color);
}
//BUTTON
void ST7735_Button_Draw(ST7735_Button *btn) {
	uint16_t tmp, i;
	uint8_t BCH, BCL;

	ST7735_DrawRectangle(btn->x, btn->y, btn->w, btn->h, btn->BorderColor);
	ST7735_AddrSet(btn->x + 1, btn->y + 1, btn->x + (btn->w - 1),
			btn->y + (btn->h - 1));
	tmp = btn->w * btn->h;

	BCL = btn->BackgroundColor & 0xFF;
	BCH = (btn->BackgroundColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
	if (btn->txt_Align == ST7735_TextAlign_Left) {
		ST7735_DrawString7x11(btn->x + 2, btn->y + 2, btn->txt, btn->TextColor,
				btn->BackgroundColor);
	}
	if (btn->txt_Align == ST7735_TextAlign_Center) {
		uint8_t tx, tlen;
		tx = (btn->w >> 1) + btn->x;
		tlen = (btn->txt_length * 7) >> 1;
		tx = tx - tlen;
		ST7735_DrawString7x11(tx, btn->y + 2, btn->txt, btn->TextColor,
				btn->BackgroundColor);
	}
	if (btn->txt_Align == ST7735_TextAlign_Right) {
		uint8_t tx, tlen;
		tx = btn->w + btn->x;
		tlen = btn->txt_length * 7;
		tx = tx - tlen - 1;
		ST7735_DrawString7x11(tx, btn->y + 2, btn->txt, btn->TextColor,
				btn->BackgroundColor);
	}
}

void ST7735_Button_StructInit(ST7735_Button *btn, uint8_t x, uint8_t y,
		char *txt, uint8_t length) {
	btn->BackgroundColor = COLOR565_BLACK;
	btn->BorderColor = COLOR565_WHITE;
	btn->TextColor = COLOR565_WHITE;
	btn->txt_Align = ST7735_TextAlign_Center;
	btn->x = x;
	btn->y = y;
	btn->w = length * 7 + 3;
	btn->h = 15;
	btn->txt = (uint8_t*) txt;
	btn->txt_length = length;
}

void ST7735_Button_Destroy(ST7735_Button *btn) {
	uint8_t BCL, BCH;
	uint16_t tmp, i;

	ST7735_AddrSet(btn->x, btn->y, btn->x + btn->w, btn->y + btn->h + 2);
	tmp = (btn->w + 1) * (btn->h + 1);

	BCL = btn->BackgroundColor & 0xFF;
	BCH = (btn->BackgroundColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
}
//ProgressBar
void ST7735_ProgressBar_Draw(ST7735_ProgressBar *pb) {
	uint16_t tmp, i;
	uint8_t CH, CL;
	uint8_t BCH, BCL;
	ST7735_DrawRectangle(pb->x, pb->y, pb->w, pb->h, pb->BorderColor);
	ST7735_AddrSet(pb->x + 1, pb->y + 1, pb->x + pb->w - 1, pb->y + pb->h - 1);

	tmp = pb->w * pb->h;

	BCL = pb->BackgroundColor & 0xFF;
	BCH = (pb->BackgroundColor >> 8) & 0xFF;

	CL = pb->ProgressColor & 0xFF;
	CH = (pb->ProgressColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}

	tmp = (pb->w * pb->progress) / 100.0f;

	ST7735_AddrSet(pb->x + 1, pb->y + 1, pb->x + tmp - 1, pb->y + pb->h - 1);

	tmp = pb->h * tmp;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(CH);
		ST7735_Send(CL);
	}
}
void ST7735_ProgressBar_SetProgress(ST7735_ProgressBar *pb, uint8_t progress) {
	if (progress > 100) {
		return;
	}
	pb->progress = progress;
	ST7735_ProgressBar_Draw(pb);
}

void ST7735_ProgressBar_StructInit(ST7735_ProgressBar *pb, uint8_t x, uint8_t y) {
	pb->BackgroundColor = COLOR565_BLACK;
	pb->BorderColor = COLOR565_WHITE;
	pb->h = 15;
	pb->progress = 0;
	pb->ProgressColor = COLOR565_BLUE;
	pb->w = 50;
	pb->x = x;
	pb->y = y;
}

void ST7735_ProgressBar_Destroy(ST7735_ProgressBar *pb) {
	uint8_t BCL, BCH;
	uint16_t tmp, i;

	ST7735_AddrSet(pb->x, pb->y, pb->x + pb->w, pb->y + pb->h + 2);
	tmp = (pb->w + 1) * (pb->h + 1);

	BCL = pb->BackgroundColor & 0xFF;
	BCH = (pb->BackgroundColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
}
//ListBox
void ST7735_ListBox_Draw(ST7735_ListBox *lb) {
	uint8_t BCH, BCL, SCH, SCL;
	uint16_t tmp, i;

	ST7735_DrawRectangle(lb->x, lb->y, lb->w, lb->h, lb->BorderColor);
	ST7735_AddrSet(lb->x + 1, lb->y + 1, lb->x + lb->w - 1, lb->y + lb->h - 1);
	tmp = lb->w * lb->h;

	BCL = lb->BackgroundColor & 0xFF;
	BCH = (lb->BackgroundColor >> 8) & 0xFF;
	SCL = lb->SelectedItemColor & 0xFF;
	SCH = (lb->SelectedItemColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}

	tmp = 0;
	for (i = 0; i < lb->items_count; i++) {
		if (lb->items[i].visible == 1) {
			uint16_t ty = lb->y + (12 * tmp) + 2;
			if (lb->items[i].selected) {
				uint16_t colored, j;
				ST7735_AddrSet(lb->x + 1, ty, lb->x + lb->w - 1, ty + 11);
				colored = lb->w * 12;
				DC_HIGH
				;
				for (j = 0; j < colored; j++) {
					ST7735_Send(SCH);
					ST7735_Send(SCL);
				}
				ST7735_DrawString7x11(lb->x + 2, ty,
						(uint8_t*) lb->items[i].text, lb->ItemTextColor,
						lb->SelectedItemColor);
			} else {
				ST7735_DrawString7x11(lb->x + 2, ty,
						(uint8_t*) lb->items[i].text, lb->ItemTextColor,
						lb->BackgroundColor);
			}
			tmp++;
		}
	}
}

void ST7735_ListBox_SetSelected(ST7735_ListBox *lb, uint8_t num) {
	uint8_t i;
	lb->SelectedItemIndex = num;
	for (i = 0; i < lb->items_count; i++) {
		lb->items[i].selected = 0;
	}
	lb->items[num].selected = 1;
	ST7735_ListBox_Draw(lb);
}

void ST7735_ListBox_SetVisibleRange(ST7735_ListBox *lb, uint8_t min,
		uint8_t max) {
	uint8_t i;
	for (i = 0; i < lb->items_count; i++) {
		lb->items[i].visible = 0;
	}
	for (i = min; i < max; i++) {
		lb->items[i].visible = 1;
	}
	ST7735_ListBox_Draw(lb);
}

ST7735_ListBox_Item ST7735_ListBox_GetSelectedItem(ST7735_ListBox *lb) {
	return lb->items[lb->SelectedItemIndex];
}

void ST7735_ListBox_StructInit(ST7735_ListBox *lb, uint8_t x, uint8_t y,
		ST7735_ListBox_Item *items, uint8_t item_count) {
	lb->BackgroundColor = COLOR565_BLACK;
	lb->BorderColor = COLOR565_WHITE;
	lb->items = items;
	lb->items_count = item_count;
	lb->ItemTextColor = COLOR565_WHITE;
	lb->SelectedItemColor = COLOR565_BLUE;
	lb->SelectedItemIndex = 0;
	lb->w = 75;
	lb->h = item_count * 12 + 2;
	lb->x = x;
	lb->y = y;
}

void ST7735_ListBox_Destroy(ST7735_ListBox *lb) {
	uint8_t BCL, BCH;
	uint16_t tmp, i;

	ST7735_AddrSet(lb->x, lb->y, lb->x + lb->w, lb->y + lb->h + 2);
	tmp = (lb->w + 1) * (lb->h + 1);

	BCL = lb->BackgroundColor & 0xFF;
	BCH = (lb->BackgroundColor >> 8) & 0xFF;
	DC_HIGH
	;
	for (i = 0; i < tmp; i++) {
		ST7735_Send(BCH);
		ST7735_Send(BCL);
	}
}
