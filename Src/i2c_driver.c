/*
 * i2c_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: NihirJyoti Muchahary
 */
#include <stdint.h>
#include "i2c_driver.h"
#include "stm32f407xx.h"
#define GPIOAEN   (0x1 << 0)
#define GPIOBEN   (0x1 << 1)
#define GPIOCEN   (0x1 << 2)

#define I2C1EN    (0x1 << 21)
#define I2C2EN    (0x1 << 22)
#define I2C3EN    (0x1 << 23)

#define I2C_START   (0x1 << 8)
#define I2C_SB      (0x1 << 0)
#define I2C_ADDR    (0x1 << 1)
#define I2C_STOP    (0x1 << 9)
#define I2C_TxE     (0x1 << 7)


#define I2C_BTF     (0x1 << 2) // Bit 2 in SR1



void I2C_Init(I2C_TypeDef* I2Cx)
{
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOBEN;
	RCC->AHB1ENR |= GPIOCEN;

	if(I2Cx==I2C1)
	{
		RCC->APB1ENR |= I2C1EN;

		// Configure PB6, PB7 as Alternate Function (AF4)
		GPIOB->MODER &= ~((0x3 << 12) | (0x3 << 14)); // clear mode
		GPIOB->MODER |=  ((0x2 << 12) | (0x2 << 14)); // set AF mode

		// Select AF4 (I2C1) for PB6, PB7
		GPIOB->AFR[0] &= ~((0xF << (6*4)) | (0xF << (7*4))); // clear AFR
		GPIOB->AFR[0] |=  ((0x4 << (6*4)) | (0x4 << (7*4))); // AF4

		// Open-drain outputs
		GPIOB->OTYPER |= (1 << 6) | (1 << 7);

		// Pull-up resistors
		GPIOB->PUPDR &= ~((0x3 << 12) | (0x3 << 14));
		GPIOB->PUPDR |=  ((0x1 << 12) | (0x1 << 14));

		I2C1->CR1 |= (0x1 << 15);
		I2C1->CR1 &= ~(0x1 << 15);

		I2C1->CR2 = 16;          // PCLK1 freq in MHz
		I2C1->CCR = 80;          // Standard mode (100 kHz)
		I2C1->TRISE = 17;        // Max rise time

		I2C1->CR1 |= (1 << 0); // Peripheral enable
	}else if(I2Cx==I2C2)
	{
		RCC->APB1ENR |= I2C2EN;

		GPIOB->MODER &= ~((0x3 << 20) | (0x3 << 22)); //for I2C1
		GPIOB->MODER |= ((0x2 << 20) | (0x2 << 22));  //for I2C1

		GPIOB->AFR[1] &= ~((0xF << 8) | (0xF << 12)); //I2C1
		GPIOB->AFR[1] |= (0x4 << 8) | (0x4 << 12);

		GPIOB->OTYPER |= (0x1 << 10) | (0x1 << 11);

		GPIOB->PUPDR  &= ~((0x3 << 20) | (0x3 << 22));
		GPIOB->PUPDR  |= ((0x1 << 20) | (0x1 << 22));

		I2C2->CR1 |= (0x1 << 15);
		I2C2->CR1 &= ~(0x1 << 15);

		I2C2->CR2 = 16;          // PCLK1 freq in MHz
		I2C2->CCR = 80;          // Standard mode (100 kHz)
		I2C2->TRISE = 17;        // Max rise time

		I2C2->CR1 |= (1 << 0); // Peripheral enable
	}else if(I2Cx==I2C3)
	{
		RCC->APB1ENR |= I2C3EN;
		GPIOA->MODER &= ~(0x3 << 16);
		GPIOC->MODER &= ~(0x3 << 18);
		GPIOA->MODER |=  (0x2 << 16);
		GPIOC->MODER |=  (0x2 << 18);

		GPIOA->AFR[1] &= ~(0xF << 0);
		GPIOC->AFR[1] &= ~(0xF << 4);

		GPIOA->AFR[1] |= (0x4 << 0);
		GPIOC->AFR[1] |= (0x4 << 4);

		GPIOA->OTYPER |= (0x1 << 8);
		GPIOC->OTYPER |= (0x1 << 9);

		GPIOA->PUPDR  &= ~(0x3 << 16);
		GPIOC->PUPDR  &= ~(0x3 << 18);

		GPIOA->PUPDR  |=  (0x3 << 16);
		GPIOC->PUPDR  |=  (0x3 << 18);

		I2C3->CR1 |= (0x1 << 15);
		I2C3->CR1 &= ~(0x1 << 15);

		I2C3->CR2 = 16;          // PCLK1 freq in MHz
		I2C3->CCR = 80;          // Standard mode (100 kHz)
		I2C3->TRISE = 17;        // Max rise time

		I2C3->CR1 |= (1 << 0); // Peripheral enable
	}
}

void I2C_Start(I2C_TypeDef* I2Cx)
{
	if(I2Cx==I2C1){
	    I2C1->CR1 |= I2C_START;
	    while(!(I2C1->SR1 & I2C_SB));
	}else if(I2Cx==I2C2){
		I2C2->CR1 |= I2C_START;
		while(!(I2C2->SR1 & I2C_SB));
	}else if(I2Cx==I2C3){
		I2C3->CR1 |= I2C_START;
		while(!(I2C3->SR1 & I2C_SB));
	}
}

void I2C_Stop(I2C_TypeDef* I2Cx)
{
    if(I2Cx == I2C1)
    {
        // 1. Wait until the TX data register is empty
        while(!(I2C1->SR1 & I2C_TxE));
        // 2. Wait until the last byte completely clears the shift register onto the bus
        while(!(I2C1->SR1 & I2C_BTF));
        // 3. Generate the actual STOP condition
        I2C1->CR1 |= I2C_STOP;
    }
    else if(I2Cx == I2C2)
    {
        while(!(I2C2->SR1 & I2C_TxE));
        while(!(I2C2->SR1 & I2C_BTF));
        I2C2->CR1 |= I2C_STOP;
    }
    else if(I2Cx == I2C3)
    {
        while(!(I2C3->SR1 & I2C_TxE));
        while(!(I2C3->SR1 & I2C_BTF));
        I2C3->CR1 |= I2C_STOP;
    }
}

void I2C_Write(I2C_TypeDef* I2Cx, uint8_t data)
{
	while(!(I2Cx->SR1 & I2C_TxE));
	I2Cx->DR = data;
}

void I2C_SendAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction)
{
    // direction: 0 = write, 1 = read
    uint8_t addr = (address << 1) | (direction & 0x1);

    I2Cx->DR = addr;

    // Wait for ADDR flag (address sent and acknowledged)
    while (!(I2Cx->SR1 & I2C_ADDR));

    // Clear ADDR by reading SR1 then SR2
    (void)I2Cx->SR1;
    (void)I2Cx->SR2;
}

uint8_t I2C_ReadData(I2C_TypeDef* I2Cx, uint8_t ack)
{
    if (ack) {
        I2Cx->CR1 |= (1 << 10); // ACK enable
    } else {
        I2Cx->CR1 &= ~(1 << 10); // ACK disable
    }

    while (!(I2Cx->SR1 & (1 << 6))); // Wait for RxNE (data register not empty)
    return I2Cx->DR;
}












