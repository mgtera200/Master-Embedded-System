/*
 * RCC_DRIVER.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Dell
 */

#ifndef INC_RCC_DRIVER_H_
#define INC_RCC_DRIVER_H_

#include "STM32F103x8.h"


#define HSI			8000000ul
#define HSE			16000000ul
#define PLL			16000000ul





uint32_t RCC_Get_SYSCLK(void);
uint32_t RCC_Get_HCLK(void);
uint32_t RCC_Get_PCLK2(void);
uint32_t RCC_Get_PCLK1(void);


#endif /* INC_RCC_DRIVER_H_ */
