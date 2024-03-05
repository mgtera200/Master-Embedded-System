/*
 * keypad.h
 *
 *ENG.TERA
 */ 
#include "GPIO_DRIVER.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define R0	0
#define R1	1
#define R2	3
#define R3	4
#define C0	5
#define	C1	6
#define	C2	7
#define C3	8




void keypad_init();
char keypad_GETKEY();


#endif /* KEYPAD_H_ */
