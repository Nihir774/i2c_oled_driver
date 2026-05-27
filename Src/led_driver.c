/*
 * i2c_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: NihirJyoti Muchahary
 */


#include <stdint.h>
#include "stm32f407xx.h"

/*
 * BEGINNING of PROTOTYPE
 */
void GPIO_InitCLK(GPIO_TypeDef* GPIOx);
void GPIO_InitOutPut(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_Input(GPIO_TypeDef* GPIOx, uint8_t pin);
void delay_ms(uint32_t ms);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t state);
uint8_t GPIO_Read(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint8_t pin);
void GPIO_ComAnode(GPIO_TypeDef* GPIOx, uint8_t pin);
void SysTick_Init(void);
void SysTick_Handler(void);
/*
 * END of PROTOTYPE
 */
#define SystemCoreClock     16000000

/*
 * GPIO CLOCK enable
 */
void GPIO_InitCLK(GPIO_TypeDef* GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}else if(GPIOx == GPIOB)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	}else if(GPIOx == GPIOC)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	}else if(GPIOx == GPIOD)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	}else if(GPIOx == GPIOE)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	}///hmmm....... that's enough maybe
}

/*
 * GPIO Initialization of OUTPUT MODE
 */
void GPIO_InitOutPut(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->MODER &= ~(0x3 << (pin*2));
	GPIOx->MODER |= (0x1 << (pin*2));

	GPIOx->OTYPER &= ~(1 << pin);

	GPIOx->OSPEEDR &= ~(0x3 << (pin*2));
	GPIOx->OSPEEDR |= (0x1 << (pin*2));
}
/*
 * GPIO Initialization of INPUT MODE
 */
void GPIO_Input(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->MODER &= ~(0x3 << (pin*2));
	GPIOx->PUPDR &= ~(0x3 << (pin*2));
}

void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t state)
{
	if(state == 1)
	{
	    GPIOx->BSRR = (0x1 << pin);
	}else
	{
		GPIOx->BSRR = (0x1 << (pin + 16));
	}
}

uint8_t GPIO_Read(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	return (uint8_t)((GPIOx->IDR >> pin) & 0x01);
}
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->ODR ^= (0x1 << pin);
}
void GPIO_ComAnode(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->BSRR = (0x1 << (pin + 16));
}

int ticks = 0;
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




















