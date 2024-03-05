/*
 * RCC_DRIVER.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Dell
 */

#include "RCC_DRIVER.h"
uint8_t AHB_Prescaler[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};
uint8_t APB2_Prescaler[] = {0,0,0,0,1,2,3,4};


uint32_t RCC_Get_SYSCLK(void){

	int x;
	x = ( (RCC->RCC_CFGR)  & (0b11 << 2) ) >> 2;
	switch (x)
	{
	case 0:
		return HSI;
		break;
	case 1:
		return HSE;
		break;
	case 2:
		return PLL;
		break;
	}
return 0;

}
uint32_t RCC_Get_HCLK(void){

	return RCC_Get_SYSCLK() >> AHB_Prescaler[ ( (RCC->RCC_CFGR) & (0b111 << 4) ) >> 4 ];


}
uint32_t RCC_Get_PCLK2(void){

	return RCC_Get_HCLK() >> APB2_Prescaler[ ( (RCC->RCC_CFGR) & (0b111 << 11) ) >> 11 ];

}

uint32_t RCC_Get_PCLK1(void){

	return RCC_Get_HCLK() >> APB2_Prescaler[ ( (RCC->RCC_CFGR) & (0b111 << 8) ) >> 8 ];

}

