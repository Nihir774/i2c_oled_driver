/*
 * main.c
 *
 *  Created on: May 19, 2026
 *      Author: NihirJyoti Muchahary
 */

#include "stm32f407xx.h"
#include "i2c_driver.h"
#include "oled_driver.h"
#include <stdint.h>



#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64

#define SystemCoreClock     16000000



volatile int ticks = 0;
void SysTick_Init(void)
{
    // SystemCoreClock defaults to 16000000 (16MHz) on boot unless RCC PLL is configured
    SysTick_Config(SystemCoreClock / 1000);
}

void delay_ms(uint32_t ms)
{
    ticks = ms;
    while(ticks > 0)
    {
        __asm__("WFI"); // Puts CPU into sleep mode until the next 1ms tick arrives
    }
}

// System Core Interrupt Handler for SysTick
void SysTick_Handler(void)
{
    if (ticks > 0)
    {
        ticks--;
    }
}
int main(void)
{
    // Step 1: Initialize I2C peripheral (I2C1 for OLED)
	SysTick_Init();

    I2C_Init(I2C1);

    // Step 2: Initialize OLED display
    SSD1306_Init();

    // Step 3: Clear screen buffer
    SSD1306_Clear();
    SSD1306_UpdateScreen();

    // Step 4: Draw something
    // Example: Draw a diagonal line
    for(int i = 0; i < 64; i++) {
        SSD1306_DrawPixel(i, i, 1);
    }
    SSD1306_UpdateScreen();
    delay_ms(2000);

    // Step 5: Animate or show text (if you add font functions later)
    while(1)
    {
        SSD1306_Clear();

        // Example: bouncing pixel
        static int x = 0, y = 0, dx = 1, dy = 1;
        SSD1306_DrawPixel(x, y, 1);
        SSD1306_UpdateScreen();

        x += dx; y += dy;
        if(x <= 0 || x >= SSD1306_WIDTH-1) dx = -dx;
        if(y <= 0 || y >= SSD1306_HEIGHT-1) dy = -dy;

        delay_ms(50);
    }
}
