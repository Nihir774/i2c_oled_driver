/*
 * main4.c
 *
 *  Created on: May 26, 2026
 *      Author: Nihirjyoti Muchahary
 */

#include "stm32f407xx.h"
#include "i2c_driver.h"
#include "oled_driver.h"
#include "bit_map.h"
#include <stdint.h>


#define SystemCoreClock   16000000

volatile int ticks = 0;

void Systick_Init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}

void delay_ms(uint32_t ms)
{
	ticks = ms;
	while(ticks > 0)
	{
		__asm__("WFI");
	}
}

void SysTick_Handler(void)
{
    if(ticks > 0)
    {
        ticks--;
    }
}


int main()
{
	//FPU enable
	SCB->CPACR |= ((3 << 10*2) | (3 << 11*2));
	__DSB();
	__ISB();

	//Init
	Systick_Init();
	I2C_Init(I2C1);
	SSD1306_Init();

	SSD1306_Clear();
	SSD1306_UpdateScreen();

	int16_t x_offset = (128 - FLOWER_BITMAP_WIDTH) / 2;
	int16_t y_offset = (64 - FLOWER_BITMAP_HEIGHT) / 2;

	while(1)
	{
		SSD1306_Clear();
		SSD1306_DrawBitMap(x_offset, y_offset, ball_bitmap, FLOWER_BITMAP_WIDTH, FLOWER_BITMAP_HEIGHT);

		SSD1306_UpdateScreen();

		delay_ms(1000);
	}

}

