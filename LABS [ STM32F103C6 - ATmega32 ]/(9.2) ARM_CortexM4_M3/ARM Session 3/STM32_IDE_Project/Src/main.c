/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
//////////////////////////////
// Eng.TERA
////////////////////////////

#include "STM32F103x8.h"
#include "GPIO_DRIVER.h"
#include "EXTI_DRIVER.h"

unsigned int flag = 0;
int Control_Register_Variable = 3;
int IPSR_Register_Variable = 3;




void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0; i<time; i++)
		for(j=0; j<255; j++);
}

void PB9_CallBack(){
	flag = 1;

	__asm(" nop " );
	__asm(" nop " );
	__asm(" nop " );

	__asm(" MRS %[out0],IPSR  "
			: [out0] "=r" (IPSR_Register_Variable) );

	__asm(" nop " );
	__asm(" nop " );
	__asm(" nop " );


}



int main(void){


	// Enable clock
	GPIOA_CLOCK_EN();
	GPIOB_CLOCK_EN();
	AFIO_CLOCK_EN();

	EXTI_Config_t EXTI_CFG;
	EXTI_CFG.EXTI_GPIO_Mapping = PB9_EXTI9;
	EXTI_CFG.Rising_or_Falling = FALLING;
	EXTI_CFG.Function_call = PB9_CallBack;
	MCAL_EXTI_init(&EXTI_CFG);
	flag =1;
	__asm(" nop " );
	__asm(" nop " );
	__asm(" nop " );

	__asm(" MRS %[out0],CONTROL  "
			: [out0] "=r" (Control_Register_Variable) );

	__asm(" nop " );
	__asm(" nop " );
	__asm(" nop " );


	while(1)
	{
		if(flag)
		{
			flag=0;
		}
	}

}
