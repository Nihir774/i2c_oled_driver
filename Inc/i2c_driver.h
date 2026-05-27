

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_
#include <stdint.h>
#include "stm32f407xx.h"


void I2C_Init(I2C_TypeDef* I2Cx);

void I2C_Start(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);



void I2C_SendAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);

void I2C_Write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx, uint8_t ack);

#endif

