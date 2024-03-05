/*
 * CortexMx_OS_Porting.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Dell
 */


#include "RTOS_inc/CortexMx_OS_Porting.h"

extern void Decide_WhatNext(void);


uint8_t SysTickLED =0;

void HardFault_Handler(void) {

	while(1);

}
void MemManage_Handler(void){

	while(1);

}
void BusFault_Handler(void){

	while(1);

}
void UsageFault_Handler(void){

	while(1);

}


__attribute ((naked)) void SVC_Handler(void)
{
	__asm("TST LR,0x4");
	__asm("ITE EQ");
	__asm("MRSEQ R0,MSP");
	__asm("MRSNE R0,PSP");
	__asm("B OS_SVC_services");



}

void HW_init(void)
{
	//Initialize Clock Tree (RCC -> SysTick Timer & CPU) 8 MHZ
	//Init HW
	//Clock Tree
	//RCC Default Values makes CPU Clock & SysTick Timer Clock = 8 MHZ


	//8 MHZ
	// 1 count -> 0.125 us
	// x count -> 1 ms
	// x = 8000 Count

	// Decrease PendSV interrupt priority to be smaller than or equal SysTick Timer
	//SysTick has a priority equal to 14
	__NVIC_SetPriority(PendSV_IRQn, 15);



}
void trigger_OS_PendSV(void){

	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


void Start_Ticker()
{

	//8 MHZ
	// 1 count -> 0.125 us
	// x count -> 1 ms
	// x = 8000 Count

	SysTick_Config(8000);

}

void SysTick_Handler(void)
{

	SysTickLED ^= 1;
	teraRTOS_Update_TaskWaitingTime();
	//Determine Pcurrent&Pnext
	Decide_WhatNext();
	//Context Switch/Restore
	trigger_OS_PendSV();

}
