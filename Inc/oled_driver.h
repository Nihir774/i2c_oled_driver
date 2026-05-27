/*
 * i2c_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: NihirJyoti Muchahary
 */

#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_


#include <stdint.h>
#include <stdbool.h>


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

// Driver API Functions
void SSD1306_Init(void);
void SSD1306_WriteCommand(uint8_t command);
void SSD1306_WriteData(uint8_t* data, uint16_t size);
void SSD1306_UpdateScreen(void);
void SSD1306_Clear(void);

// Basic Graphics Functions
void SSD1306_DrawPixel(int16_t x, int16_t y, uint8_t color);
void SSD1306_DrawBitMap(int16_t x_start, int16_t y_start, const uint8_t *bitmap, int16_t w, int16_t h);



#endif /* OLED_DRIVER_H_ */
