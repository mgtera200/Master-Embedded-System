/*
ENG-TERA
 */

#ifndef STUDENTBASE_H_
#define STUDENTBASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "conio.h"
#define DPRINTF(...) {fflush(stdout); \
	                  fflush(stdin); \
	                  printf(__VA_ARGS__); \
                      fflush(stdout); \
	                  fflush(stdin);}
typedef struct{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[10];
}sinfo;
typedef struct{
	sinfo* head;
	sinfo* base;
	sinfo* tail;
	int count;
	int length;
}fifo;
typedef enum{
	queue_full,
	queue_no_error,
	queue_empty,
	queue_NULL
}queue_status;
queue_status Fifo_init(fifo *pFifo,sinfo *buff);
void enqueue(fifo *pFifo,sinfo *new_student);
void add_student_file(fifo *pFifo);
void add_student_manually(fifo *pFifo);
void find_r1(fifo *pFifo);
void find_fn(fifo *pFifo);
void find_c(fifo *pFifo);
void tot_s(fifo *pFifo);
void del_s(fifo *pFifo);
void up_s(fifo *pFifo);
void show_s(fifo *pFifo);

#endif /* STUDENTBASE_H_ */
