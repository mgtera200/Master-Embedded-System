/*
 * TERA_RTOS_FIFO.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Dell
 */

#ifndef RTOS_INC_TERA_RTOS_FIFO_H_
#define RTOS_INC_TERA_RTOS_FIFO_H_

#include "stdio.h"
#include"stdint.h"
#include "Scheduler.h"
/*customer can select element type */
#define element_type Task_Creation*
typedef struct{
	unsigned int counter;
	element_type* head;
	element_type* tail;
	element_type* base;
	unsigned int  length;
}FIFO_Buf_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL,

}Buffer_status;

/*APIs*/

Buffer_status FIFO_init (FIFO_Buf_t* fifo,element_type* buff , unsigned int length);
Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo,element_type item);
Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo,element_type* item);
Buffer_status FIFO_is_full (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);

#endif /* RTOS_INC_TERA_RTOS_FIFO_H_ */
