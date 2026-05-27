/*
 * i2c_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: NihirJyoti Muchahary
 */
// Driver API Functions
#include "i2c_driver.h"
#include <stdint.h>
#include "oled_driver.h"

// Screen Dimensions
#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64
#define SSD1306_BUFFER_SIZE      ((SSD1306_WIDTH * SSD1306_HEIGHT) / 8) // 1024 bytes



static uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE];

// Your I2C Slave Address (Modify if your physical pin shifts it)
#define SSD1306_I2C_ADDR         0x3C

// Core SSD1306 Commands from Datasheet
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COLUMNADDR          0x21
#define SSD1306_PAGEADDR            0x22
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_CHARGEPUMP          0x8D
#define SSD1306_SEGREMAP            0xA1 // Modified to 0xA1 for correct orientation
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_RIGHT_HORIZONTAL_SCROLL (0x26)

#define SSD1306_LEFT_HORIZONTAL_SCROLL (0x27)
#define SSD1306_ACTIVATE_SCROLL (0x2F)
#define SSD1306_DEACTIVATE_SCROLL (0x2E)
#define SSD1306_SETSTARTLINE (0x40)
#define SSD1306_SETLOWCOLUMN (0x00)
#define SSD1306_SETHIGHCOLUMN (0x10)





// Driver API Functions
void SSD1306_Init(void)
{
	SSD1306_WriteCommand(SSD1306_DISPLAYOFF);
	SSD1306_WriteCommand(SSD1306_SETDISPLAYCLOCKDIV);
	SSD1306_WriteCommand(0x80);
	SSD1306_WriteCommand(SSD1306_SETMULTIPLEX);
	SSD1306_WriteCommand(0x3F);
	SSD1306_WriteCommand(SSD1306_SETDISPLAYOFFSET);
	SSD1306_WriteCommand(0x00);
	SSD1306_WriteCommand(0x40);
	SSD1306_WriteCommand(SSD1306_CHARGEPUMP);
	SSD1306_WriteCommand(0x14);
	SSD1306_WriteCommand(SSD1306_MEMORYMODE);
	SSD1306_WriteCommand(0x00);
	SSD1306_WriteCommand(SSD1306_SEGREMAP);
	SSD1306_WriteCommand(SSD1306_COMSCANDEC);
	SSD1306_WriteCommand(SSD1306_SETCOMPINS);
	SSD1306_WriteCommand(0x12);
	SSD1306_WriteCommand(SSD1306_SETCONTRAST);
	SSD1306_WriteCommand(0xCF);
	SSD1306_WriteCommand(SSD1306_SETPRECHARGE);
	SSD1306_WriteCommand(0xF1);
	SSD1306_WriteCommand(SSD1306_SETVCOMDETECT);
	SSD1306_WriteCommand(0x40);
    SSD1306_WriteCommand(SSD1306_DISPLAYALLON_RESUME); // 0xA4
    SSD1306_WriteCommand(SSD1306_NORMALDISPLAY);       // 0xA6
    SSD1306_WriteCommand(SSD1306_DISPLAYON);           // 0xAF
}
void SSD1306_WriteCommand(uint8_t command)
{
	I2C_Start(I2C1);
	I2C_SendAddress(I2C1, SSD1306_I2C_ADDR, 0); // write
	I2C_Write(I2C1, 0x00);
	I2C_Write(I2C1, command);
	I2C_Stop(I2C1);
}
void SSD1306_WriteData(uint8_t* data, uint16_t size)
{
	I2C_Start(I2C1);
	I2C_SendAddress(I2C1,SSD1306_I2C_ADDR, 0);
	I2C_Write(I2C1, 0x40);
	for(uint16_t i = 0; i < size ; i++){
		I2C_Write(I2C1, data[i]);
	}
	I2C_Stop(I2C1);
}
void SSD1306_UpdateScreen(void)
{
	for (uint8_t page = 0; page < 8; page++){
		SSD1306_WriteCommand(0xB0 + page); //page address
		SSD1306_WriteCommand(0x00);
		SSD1306_WriteCommand(0x10);
		SSD1306_WriteData(&SSD1306_Buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
	}
}
void SSD1306_Clear(void)
{
	for(uint16_t i=0; i< sizeof(SSD1306_Buffer); i++){
		SSD1306_Buffer[i] = 0x00;
	}
}

// Basic Graphics Functions
void SSD1306_DrawPixel(int16_t x, int16_t y, uint8_t color)
{
	if(x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT)return ;

	if(color)
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
	}else
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

void SSD1306_DrawBitMap(int16_t x_start, int16_t y_start, const uint8_t *bitmap, int16_t w, int16_t h)
{
	int16_t byteWidth = (w + 7) / 8; //horizontal row byte bounds
	uint8_t byteValue = 0;

	for(int16_t j = 0;j < h; j ++){
		for(int16_t i = 0;i < w; i ++){
			if(i & 7){
				byteValue <<= 1;
			}else{
				byteValue = bitmap[j * byteWidth + (i/8)];
			}
			if(byteValue & 0x80){
				SSD1306_DrawPixel(x_start + i, y_start + j, 1);
			}
		}
	}
}

