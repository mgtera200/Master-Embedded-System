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
Task_Creation teraRTOS_idleTask;

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


typedef enum {
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_WaitingTask
}SVC_ID;


//Handler Mode
void BubbleSort(){

	uint8_t i=0;
	uint8_t j=0;
	uint8_t n;


	Task_Creation * temp;
	n = OS_Control.ActiveTasks_number;

	for(i=0; i<n-1; i++)
	{
		for(j=0; j<n-i-1; j++)
		{
			if (OS_Control.OS_Tasks[j]->Priority > OS_Control.OS_Tasks[j+1]->Priority)
			{
				temp = OS_Control.OS_Tasks[j];
				OS_Control.OS_Tasks[j] = OS_Control.OS_Tasks[j+1];
				OS_Control.OS_Tasks[j+1] = temp;
			}

		}
	}


}

//Handler MODE
void teraRTOS_Update_SchedulerTable(){

	Task_Creation * Ptask;
	Task_Creation * PnextTask;

	int i = 0 ;



	Task_Creation * temp = NULL;

	//1- Bubble sort the scheduler table -> OS_Control.OS_Tasks[100] (FROM HIGH PRIORITY TO LOW)
	BubbleSort();
	//2- Free ready queue
	while(FIFO_dequeue(&Ready_Queue, &temp) != FIFO_EMPTY);

	//3- Update ready queue
	while(i< OS_Control.ActiveTasks_number)
	{
		Ptask =	OS_Control.OS_Tasks[i];
		PnextTask =	OS_Control.OS_Tasks[i+1];
		if(Ptask->TaskState != Suspended)
		{
			if(PnextTask->TaskState == Suspended)
			{
				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask->TaskState = Ready;
				break;
			}
			if(Ptask->Priority < PnextTask->Priority)
			{
				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask->TaskState = Ready;
				break;
			}
			else if( (Ptask->Priority) == (PnextTask->Priority) )
			{
				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask->TaskState = Ready;
			}
			else if(Ptask->Priority > PnextTask->Priority) // This condition not allowed to happen because of Bubble sorting
			{
				break;
			}
		}



		i++;
	}

}

//Handler Mode
void Decide_WhatNext(void)
{

	//if ready queue is empty && OS_Control.CurrentTask->TaskState != Suspended
	if(Ready_Queue.counter == 0 && OS_Control.CurrentTask->TaskState != Suspended)
	{
		OS_Control.CurrentTask->TaskState = Running;
		FIFO_enqueue(&Ready_Queue, OS_Control.CurrentTask);
		OS_Control.NextTask =  OS_Control.CurrentTask;
	}
	else{
		FIFO_dequeue(&Ready_Queue, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running;
		if( (OS_Control.CurrentTask->Priority == OS_Control.NextTask->Priority ) && (OS_Control.CurrentTask->TaskState != Suspended) )
		{
			FIFO_enqueue(&Ready_Queue, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState = Ready;
		}
	}

}

//To execute specific OS service
// Handler Mode
void OS_SVC_services(int * StackFramePointer)
{
	//OS_SVC_Set Stack -> R0 -> argument 0 = StackFramePointer
	//OS_SVC_Set Stack : R0,R1,R2,R3,R12,LR,PC,xPSR
	unsigned char SVC_Number;
	SVC_Number =  *((unsigned char*)( ( (unsigned char*)StackFramePointer[6] ) - 2 )) ;

	switch(SVC_Number)
	{
	case SVC_ActivateTask: //Activate Task
	case SVC_TerminateTask: //Terminate Task
		//Update Scheduler table and update ready queue
		teraRTOS_Update_SchedulerTable();
		//If OS is in running state -> decide what to run next -> trigger OS_PendSV(Switch Context/Restore)
		if(OS_Control.OS_Modes == OSrunning)
		{
			if(strcmp(OS_Control.CurrentTask->TaskName, "idleTask") != 0)
			{
				//Decide what next
				Decide_WhatNext();

				//trigger OS_PendSV(Switch Context/Restore)
				trigger_OS_PendSV();

			}
		}
		break;
	case SVC_WaitingTask:
		teraRTOS_Update_SchedulerTable();

		break;
	}

	return;
}

__attribute ((naked)) void PendSV_Handler(void)
{
	//=====================================
	//Save the Context of the Current Task
	//=====================================
	//Get the Current Task PSP from CPU register as CPU pushes xPSR,.....,R0

	OS_GET_PSP(OS_Control.CurrentTask->CurrentPSP);

	//Using this CurrentPSP ( Pointer ) to store (R4 to R11)
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r4" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r5" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r6" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r7" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r8" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r9" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r10" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );
	OS_Control.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0,r11" : "=r" (*(OS_Control.CurrentTask->CurrentPSP)) );

	//Save the current Valure of PSP
	//Already saved in CurrentPSP

	//=====================================
	//Restore the Context of the Next task
	//=====================================
	if(OS_Control.NextTask != NULL){
		OS_Control.CurrentTask = OS_Control.NextTask;
		OS_Control.NextTask = NULL;
	}

	__asm volatile("mov R11,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R10,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R9,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R8,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R7,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R6,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R5,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;
	__asm volatile("mov R4,%0 " : : "r"( *(OS_Control.CurrentTask->CurrentPSP) ));
	OS_Control.CurrentTask->CurrentPSP++;

	//Update PSP and Exit
	OS_SET_PSP(OS_Control.CurrentTask->CurrentPSP);
	__asm volatile ("BX LR");



}


void teraRTOS_CreateMSP() {
	OS_Control._S_MSP =(uint32_t)&_estack ;
	OS_Control._E_MSP = OS_Control._S_MSP - MainStackSize;
	// Aligned 8 Bytes spaces between MSP and PSP
	OS_Control.Task_PSP_LOCATOR = OS_Control._E_MSP + 8 ;

	//  if ( _E_MSP < &_eheap ) --> " ERROR: EXCEEDED THE AVAILABLE STACK SIZE "


}
uint8_t idleTaskLED;
void idle_Task_fun(){

	while(1)
	{
		idleTaskLED ^= 1;
		__asm("wfe");
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
	strcpy (teraRTOS_idleTask.TaskName,"idleTask");
	teraRTOS_idleTask.Priority = 255;
	teraRTOS_idleTask.TaskEntry_Ptr = idle_Task_fun;
	teraRTOS_idleTask.Stack_Size = 300;

	RTOS_Error = teraRTOS_CreateTask(&teraRTOS_idleTask);



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


	OS_Control.OS_Tasks[OS_Control.ActiveTasks_number] = create;
	OS_Control.ActiveTasks_number++;
	// Task state update --> Suspended

	create->TaskState = Suspended;



	return RTOS_Error;
}
//Thread Mode
void teraRTOS_OS_SVC_Set(SVC_ID id){

	switch(id)
	{
	case SVC_ActivateTask:
		__asm("SVC #0x0");

		break;
	case SVC_TerminateTask:
		__asm("SVC #0x1");


		break;
	case SVC_WaitingTask:
		__asm("SVC #0x2");



		break;

	}

}


TERA_RTOS_ErrorType teraRTOS_ActivateTask(Task_Creation * activate){

	TERA_RTOS_ErrorType error;
	error = NoError;

	activate->TaskState = Waiting;
	teraRTOS_OS_SVC_Set(SVC_ActivateTask);



	return error;

}
TERA_RTOS_ErrorType teraRTOS_TerminateTask(Task_Creation * terminate){

	TERA_RTOS_ErrorType error;
	error = NoError;

	terminate->TaskState = Suspended;
	teraRTOS_OS_SVC_Set(SVC_TerminateTask);




	return error;



}


void teraRTOS_TaskWait(uint32_t TicksNum,Task_Creation * task_w8)
{

	task_w8->Task_WaitingTime.Blocking = Block_Enable;
	task_w8->Task_WaitingTime.Ticks_Number = TicksNum;
	//Task should be suspended
	//Then should be terminated
	teraRTOS_TerminateTask(task_w8);

}
void teraRTOS_START(){

	OS_Control.OS_Modes = OSrunning;
	//Set default Current Task == idleTask
	OS_Control.CurrentTask = &teraRTOS_idleTask;
	//Activate idle task
	teraRTOS_ActivateTask(&teraRTOS_idleTask);
	//Start ticker
	Start_Ticker(); // Every 1ms

	OS_SET_PSP(OS_Control.CurrentTask->CurrentPSP);

	//Switch from MSP to PSP
	OS_SWITCH_SP_to_PSP;

	Switch_CPU_AccessLevel_Unprivilege;

	teraRTOS_idleTask.TaskEntry_Ptr();


}

void teraRTOS_Update_TaskWaitingTime()
{
	int i=0;
	for(i=0; i<OS_Control.ActiveTasks_number; i++)
	{

		if(OS_Control.OS_Tasks[i]->TaskState == Suspended)
		{
			if(OS_Control.OS_Tasks[i]->Task_WaitingTime.Blocking == Block_Enable)
			{
				OS_Control.OS_Tasks[i]->Task_WaitingTime.Ticks_Number--;
				if(OS_Control.OS_Tasks[i]->Task_WaitingTime.Ticks_Number == 0)
				{
					OS_Control.OS_Tasks[i]->Task_WaitingTime.Blocking = Block_Disable;
					OS_Control.OS_Tasks[i]->TaskState = Waiting;
					teraRTOS_OS_SVC_Set(SVC_WaitingTask);

				}

			}

		}
	}

}

TERA_RTOS_ErrorType teraRTOS_AcquireMutex(Mutex_Creation * mutex, Task_Creation * user){

	if(mutex->CurrentTaskUser == NULL)
	{
		mutex->CurrentTaskUser = user;

		return NoError;
	}

	else
	{
		if(mutex->NextTaskUser == NULL)
		{
			mutex->NextTaskUser = user;
			teraRTOS_TerminateTask(user);

			return NoError;
		}
		else
		{
			return MutexFull;
		}

	}
}

TERA_RTOS_ErrorType teraRTOS_ReleaseMutex(Mutex_Creation * mutex){

	if(mutex->CurrentTaskUser != NULL)
	{
		mutex->CurrentTaskUser = mutex->NextTaskUser;
		mutex->NextTaskUser = NULL ;
		teraRTOS_ActivateTask(mutex->CurrentTaskUser);

		return NoError;
	}
	else
	{
		return MutexAlreadyReleased;
	}

}
