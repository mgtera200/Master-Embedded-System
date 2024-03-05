/*
 * CortexMx_OS_Porting.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Dell
 */

#ifndef RTOS_INC_CORTEXMX_OS_PORTING_H_
#define RTOS_INC_CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"

extern uint32_t _estack;
extern uint32_t _eheap;




#define MainStackSize						2048
#define OS_SET_PSP(Address_InputVariable)	__asm volatile("MSR PSP,%[in0] " : : [in0] "r" (Address_InputVariable))
#define OS_GET_PSP(Address_OutputVariable)	__asm volatile("MRS %[out0],PSP " : [out0] "=r" (Address_OutputVariable))
#define OS_SWITCH_SP_to_PSP					__asm volatile("MRS R0,CONTROL \n\t MOV R1,0x02 \n\t ORR R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_SWITCH_SP_to_MSP					__asm volatile("MRS R0,CONTROL \n\t MOV R1,0x05 \n\t AND R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_Generate_Exception				__asm volatile("SVC #0x3")
#define Switch_CPU_AccessLevel_Privilege    __asm volatile("MRS R3,CONTROL \n\t LSR R3,R3,#0x1 \n\t LSL R3,R3,#0x1 \n\t MSR CONTROL,R3")// Clear bit 0 CONTROL reg
#define Switch_CPU_AccessLevel_Unprivilege  __asm volatile("MRS R3,CONTROL \n\t ORR R3,R3,#0x1 \n\t MSR CONTROL,R3")// Set bit 0 CONTROL reg




void HW_init(void);
void trigger_OS_PendSV();
void Start_Ticker();

#endif /* RTOS_INC_CORTEXMX_OS_PORTING_H_ */
