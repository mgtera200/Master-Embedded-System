/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
typedef volatile unsigned int vuint32_t;
#include <stdint.h>
#define RCC_Base 0x40021000
#define PORTA_Base 0x40010800
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_Base + 0x18)
#define GPIO_CRH    *(volatile uint32_t *)(PORTA_Base + 0x04)
#define GPIO_ODR    *(volatile uint32_t *)(PORTA_Base + 0x0C)
//bit fields
#define RCC_IOPAEN	(1<<2)
#define GPIOA13		(1UL<<13)
typedef union{
	vuint32_t 		all_fields;
	struct{
		vuint32_t 	reserved:13;
		vuint32_t	P_13:1;

	}Pin;
}R_ODR_t;
volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORTA_Base + 0x0C);

int main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIO_CRH &= 0xFF0FFFFF;
	GPIO_CRH |= 0x0020000;
	while(1)
	{
		R_ODR->Pin.P_13 = 1;
		for(int i = 0; i < 5000; i++);
		R_ODR->Pin.P_13 = 0;
		for(int i = 0; i < 5000; i++);
	}
	return 0;
}