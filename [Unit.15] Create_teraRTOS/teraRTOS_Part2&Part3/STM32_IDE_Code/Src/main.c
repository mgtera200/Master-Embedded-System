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
#include "Scheduler.h"
#include "core_cm3.h"
#include "CortexMx_OS_Porting.h"


uint8_t Task1LED,Task2LED,Task3LED,Task4LED=0;


void task1(void) {

	while(1)
	{
		//Task 1 code
		Task1LED ^= 1;
	}
}

void task2(void) {

	while(1)
	{
		//Task 2 code
		Task2LED ^= 1;

	}
}

void task3(void) {

	while(1)
	{
		//Task 3 code
		Task3LED ^= 1;

	}
}


Task_Creation Task1,Task2,Task3;

int main(void){

	TERA_RTOS_ErrorType Error;
	//HW INIT (Initialize ClockTree, ResetController)
	HW_init();

	if(TERA_RTOS_init() != NoError)
		while(1);

	Task1.Stack_Size = 1024;
	Task1.TaskEntry_Ptr = task1;
	Task1.Priority = 3;
	strcpy(Task1.TaskName, "Task_1");

	Task2.Stack_Size = 1024;
	Task2.TaskEntry_Ptr = task2;
	Task2.Priority = 3;
	strcpy(Task2.TaskName, "Task_2");

	Task3.Stack_Size = 1024;
	Task3.TaskEntry_Ptr = task3;
	Task3.Priority = 3;
	strcpy(Task3.TaskName, "Task_3");

	Error = teraRTOS_CreateTask(&Task1);
	Error = teraRTOS_CreateTask(&Task2);
	Error = teraRTOS_CreateTask(&Task3);

	teraRTOS_ActivateTask(&Task1);
	teraRTOS_ActivateTask(&Task2);
	teraRTOS_ActivateTask(&Task3);

	teraRTOS_START();




	while(1)
	{


	}

}