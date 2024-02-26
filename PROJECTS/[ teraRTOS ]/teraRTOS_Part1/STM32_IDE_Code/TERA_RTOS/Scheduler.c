/*
 * Scheduler.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Dell
 */

#include "Scheduler.h"
#include "TERA_RTOS_FIFO.h"


FIFO_Buf_t Ready_Queue;
Task_Creation * READY_QUEUE_FIFO[100];
Task_Creation idle_Task_Creation;

struct {

	Task_Creation * OS_Tasks[100];    // Table of tasks
	uint32_t _S_MSP; 		     // NOT ENTERED BY THE USER
	uint32_t _E_MSP;  	        // NOT ENTERED BY THE USER
	uint32_t Task_PSP_LOCATOR;     // NOT ENTERED BY THE USER
	uint32_t ActiveTasks_number;  // NOT ENTERED BY THE USER
	Task_Creation * CurrentTask; // Pointer to the task currently getting executed
	Task_Creation * NextTask;   // Pointer to the next task getting executed
	enum {
		OSsuspended,
		OSrunning
	}OS_Modes;
}OS_Control;


//To execute specific OS service

void OS_SVC_services(int * StackFramePointer)
{
	//OS_SVC_Set Stack -> R0 -> argument 0 = StackFramePointer
	//OS_SVC_Set Stack : R0,R1,R2,R3,R12,LR,PC,xPSR
	unsigned char SVC_Number;
	SVC_Number =  *((unsigned char*)( ( (unsigned char*)StackFramePointer[6] ) - 2 )) ;

	switch(SVC_Number)
	{
	case 1: //Activate Task
		break;
	case 2: //Terminate Task
		break;
	case 3:
		break;
	}

	return;
}

void PendSV_Handler(void)
{

}

void OS_SVC_Set(int SVC_ID)
{
	switch(SVC_ID)
	{
	case 1: //Activate Task
		__asm("svc #0x01");
		break;
	case 2: //Terminate Task
		__asm("svc #0x02");
		break;
	case 3: //
		__asm("svc #0x03");
		break;
	case 4: //PendSV
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;

	}
}
void teraRTOS_CreateMSP() {
	OS_Control._S_MSP =(uint32_t)&_estack ;
	OS_Control._E_MSP = OS_Control._S_MSP - MainStackSize;
	// Aligned 8 Bytes spaces between MSP and PSP
	OS_Control.Task_PSP_LOCATOR = OS_Control._E_MSP + 8 ;

	//  if ( _E_MSP < &_eheap ) --> " ERROR: EXCEEDED THE AVAILABLE STACK SIZE "


}
void idle_Task_fun(){

	while(1)
	{
		__asm("NOP");
	}

}
TERA_RTOS_ErrorType TERA_RTOS_init(void){

	TERA_RTOS_ErrorType RTOS_Error;
	RTOS_Error = NoError;
	//Update OS Mode ( OS -> suspended )
	OS_Control.OS_Modes = OSsuspended;

	// Specify the main stack for OS
	teraRTOS_CreateMSP();


	// Create OS ready Queue
	if ( FIFO_init(&Ready_Queue, READY_QUEUE_FIFO, 100) != FIFO_NO_ERROR)
	{
		RTOS_Error = Ready_Queue_init_error;
	}


	// Configure idle Task
	strcpy (idle_Task_Creation.TaskName,"idleTask");
	idle_Task_Creation.Priority = 255;
	idle_Task_Creation.TaskEntry_Ptr = idle_Task_fun;
	idle_Task_Creation.Stack_Size = 300;

	RTOS_Error = teraRTOS_CreateTask(&idle_Task_Creation);



	return RTOS_Error;

}


void teraRTOS_Create_TaskStack(Task_Creation * create_stack){

			/* Task stack frame
			 * ================
			 * (Registers that saved/restored automatically)
//Old SP --> *
			 * xPSR
			 * PC
			 * LR
			 * R12
			 * R3
			 * R2
			 * R1
			 * R0
			 * ================
			 * (Registers that saved/restored manually)
			 * R4
			 * R5
			 * R6
			 * R7
			 * R8
			 * R9
			 * R10
//New SP --> * R11
			 */

	create_stack->CurrentPSP =(uint32_t *) create_stack->_S_PSP_Task;

	create_stack->CurrentPSP--;
	*(create_stack->CurrentPSP)=0x01000000;		//Dummy xPSR with T=1 to avoid Bus fault

	create_stack->CurrentPSP--;
	*(create_stack->CurrentPSP)=(unsigned int)create_stack->TaskEntry_Ptr;

	create_stack->CurrentPSP--;
	*(create_stack->CurrentPSP)=0xFFFFFFFD; // LR = 0xFFFFFFFD (EXC_RETURN) --> return to Thread with PSP

	int i;
	for(i=0; i<13; i++)
	{
		create_stack->CurrentPSP--;
		*(create_stack->CurrentPSP)=0;
	}




}


TERA_RTOS_ErrorType teraRTOS_CreateTask(Task_Creation* create){

	TERA_RTOS_ErrorType RTOS_Error = NoError;

	//Create its own PSP stack

	create->_S_PSP_Task = OS_Control.Task_PSP_LOCATOR;
	create->_E_PSP_Task = create->_S_PSP_Task - create->Stack_Size;

	//Check task stack size exceeded PSP stack or not

	if( create->_E_PSP_Task < (uint32_t)&(_eheap) )
	{
		return Task_exceeded_StackSize;
	}

	//Aligned 8 bytes space between task PSP and other

	OS_Control.Task_PSP_LOCATOR = ( create->_E_PSP_Task - 8 );


	//Initialize PSP task stack

	teraRTOS_Create_TaskStack(create);

	// Task state update --> Suspended

	create->TaskState = Suspended;



	return RTOS_Error;
}
