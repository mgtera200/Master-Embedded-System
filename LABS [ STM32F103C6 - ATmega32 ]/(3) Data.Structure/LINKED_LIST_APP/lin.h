/*
 * lin.h
 *
 *  Created on: Sep 2, 2023
 *      Author: MOHTERA
 */

#ifndef LIN_H_
#define LIN_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#define dprintf(...) {fflush(stdout); \
	                  fflush(stdin); \
	                  printf(__VA_ARGS__); \
                      fflush(stdout); \
	                  fflush(stdin);}
struct Sstudents {
	int id;
	char name[40];
	float height;
};
struct Snode {
	struct Sstudents data;
	struct Sstudents* pNext_student;
};
void add_student();
int Delete_student();
void view_students();
void Delete_all();
void GetNth();
void length();
void reverse_index();
void middle();
int loop();

#endif /* LIN_H_ */
