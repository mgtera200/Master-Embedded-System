/*
 * Scheduler.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Dell
 */

#ifndef RTOS_INC_SCHEDULER_H_
#define RTOS_INC_SCHEDULER_H_

#include "CortexMx_OS_Porting.h"
#include <string.h>


typedef enum{
	NoError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize,
	MutexFull,
	MutexAlreadyReleased

}TERA_RTOS_ErrorType;


typedef struct{

	uint32_t Stack_Size;
	uint8_t Priority;
	void (* TaskEntry_Ptr)(void); // Pointer to task C_Function
	uint8_t Task_AutoStart;
	uint32_t _S_PSP_Task;  // NOT ENTERED BY THE USER
	uint32_t _E_PSP_Task;  // NOT ENTERED BY THE USER
	uint32_t * CurrentPSP; // NOT ENTERED BY THE USER
	char TaskName[30];
	enum {

		Suspended,
		Running,
		Waiting,
		Ready

	}TaskState; //NOT ENTERED BY THE USER

	struct {

		enum {
			Block_Enable,
			Block_Disable
		}Blocking;

		uint32_t Ticks_Number;

	}Task_WaitingTime;



}Task_Creation;

typedef struct {

	uint8_t * Payload_P;
	uint32_t PayloadSize;
	Task_Creation * CurrentTaskUser;
	Task_Creation * NextTaskUser;
	char Mutex_Name[30];


}Mutex_Creation;



//APIs

TERA_RTOS_ErrorType TERA_RTOS_init(void);
TERA_RTOS_ErrorType teraRTOS_CreateTask(Task_Creation * create);
TERA_RTOS_ErrorType teraRTOS_ActivateTask(Task_Creation * activate);
TERA_RTOS_ErrorType teraRTOS_TerminateTask(Task_Creation * terminate);
void teraRTOS_START();
void teraRTOS_TaskWait(uint32_t TicksNum,Task_Creation * task_w8);
TERA_RTOS_ErrorType teraRTOS_AcquireMutex(Mutex_Creation * mutex, Task_Creation * user);
TERA_RTOS_ErrorType teraRTOS_ReleaseMutex(Mutex_Creation * mutex);






#endif /* RTOS_INC_SCHEDULER_H_ */
