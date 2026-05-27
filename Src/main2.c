/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body using custom GPIO API
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f407xx.h"

// Forward declarations of your API functions (if not using a separate .h file)
void GPIO_InitCLK(GPIO_TypeDef* GPIOx);
void GPIO_InitOutPut(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_Input(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t state);
uint8_t GPIO_Read(GPIO_TypeDef* GPIOx, uint8_t pin);
void delay_ms(uint32_t ms);
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_ComAnode(GPIO_TypeDef* GPIOx, uint8_t pin);
void SysTick_Init(void);
void SysTick_Handler(void);
// Helper function to turn off all three LEDs cleanly
void Clear_All_LEDs(void)
{
    // Direct register manipulation to clear bits 0, 1, and 2
    GPIOD->BSRR = ((1 << 0) | (1 << 1) | (1 << 2));
}


int main(void)
{
    // 1. Enable peripheral clocks for Port A and Port D
    GPIO_InitCLK(GPIOA);
    GPIO_InitCLK(GPIOD);

    // 2. Configure PA0 as an Input (User Button)
    GPIO_Input(GPIOA, 0);

    // 3. Configure PD0, PD1, and PD2 as Outputs (LEDs)
    GPIO_InitOutPut(GPIOD, 0);
    GPIO_InitOutPut(GPIOD, 1);
    GPIO_InitOutPut(GPIOD, 2);
    SysTick_Init();
    // Make sure everything starts turned off
    Clear_All_LEDs();

    while(1)
    {
        // Step 1: Turn on PD0
    	Clear_All_LEDs();
        GPIO_ComAnode(GPIOD, 0);
        delay_ms(500);

        // Step 2: Turn on PD1
    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 1);
    	delay_ms(500);
    	//
    	//Step 3: Turn on PD2
    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 2);
    	delay_ms(500);

    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 0);
    	GPIO_ComAnode(GPIOD, 1);
    	delay_ms(500);

    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 1);
    	GPIO_ComAnode(GPIOD, 2);
    	delay_ms(500);

    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 2);
    	GPIO_ComAnode(GPIOD, 0);
    	delay_ms(500);

    	Clear_All_LEDs();
    	GPIO_ComAnode(GPIOD, 0);
    	GPIO_ComAnode(GPIOD, 1);
    	GPIO_ComAnode(GPIOD, 2);
        delay_ms(500);

    }
}
