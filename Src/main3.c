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
#include <math.h> // Required for sin() and cos() calculations

#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64

#define SystemCoreClock     16000000

// Center coordinates for our rose
#define CENTER_X                 (SSD1306_WIDTH / 2)
#define CENTER_Y                 (SSD1306_HEIGHT / 2)

volatile int ticks = 0;
void SysTick_Init(void)
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
    if (ticks > 0)
    {
        ticks--;
    }
}

int main(void)
{
    // Initialize System Tick Timer
    SysTick_Init();

    // Step 1: Initialize I2C peripheral
    I2C_Init(I2C1);

    // Step 2: Initialize OLED display
    SSD1306_Init();

    // Step 3: Clear screen buffer completely
    SSD1306_Clear();
    SSD1306_UpdateScreen();

    // Variables for the blooming mathematical animation
    float current_radius = 0.0f;     // Starts at 0 (bud stage)
    float max_radius = 28.0f;        // Maximum size of the rose (fits nicely vertically)
    float bloom_speed = 0.4f;        // How fast the rose expands per frame

    // Changing 'n' changes the number of petals.
    // If n is odd, number of petals = n (e.g., 5). If n is even, petals = 2n (e.g., 4 * 2 = 8)
    float n = 5.0f;

    while(1)
    {

    	// Enable Hardware FPU Coprocessors (CP10 and CP11)
    	    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  // Full access to FPU
    	    __DSB();
    	    __ISB();

    	    // Now initialize the rest of your system safely
    	    SysTick_Init();
    	    I2C_Init(I2C1);
    	    SSD1306_Init();


        // Clear the screen buffer for the next frame of animation
        SSD1306_Clear();

        // Draw the mathematical rose structure based on the current bloom radius
        // We sweep theta from 0 to 360 degrees (converted to radians)
        for (float theta = 0.0f; theta < 2.0f * 3.14159f; theta += 0.01f)
        {
            // Calculate the relative length of the petal at this specific angle
            float r = current_radius * sinf(n * theta);

            // Convert polar coordinates (r, theta) to Cartesian screen coordinates (x, y)
            int16_t x = (int16_t)(CENTER_X + r * cosf(theta));
            int16_t y = (int16_t)(CENTER_Y + r * sinf(theta));

            // Plot the pixel into our screen RAM buffer
            SSD1306_DrawPixel(x, y, 1);
        }

        // Push the freshly calculated frame to the physical display
        SSD1306_UpdateScreen();

        // Expand the flower radius to create the blooming effect
        current_radius += bloom_speed;

        // Loop control: Once fully bloomed, hold it, then reset back to a bud
        if (current_radius > max_radius)
        {
            delay_ms(3000);          // Hold the fully bloomed rose on screen for 3 seconds
            current_radius = 0.0f;   // Reset back to a closed bud

            // Cycle the petal numbers for the next loop to keep it interesting!
            n = (n == 5.0f) ? 4.0f : (n == 4.0f) ? 7.0f : 5.0f;
        }

        delay_ms(30); // Frame delay control (roughly 33 FPS)
    }





}
