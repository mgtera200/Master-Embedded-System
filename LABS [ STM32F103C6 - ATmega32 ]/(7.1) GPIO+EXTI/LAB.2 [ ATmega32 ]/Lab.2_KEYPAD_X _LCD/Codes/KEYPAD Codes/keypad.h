/*
 * keypad.h
 *
 * Created: 11/10/2023 9:42:06 PM
 *  Author: Dell
 */ 
#include "address.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define R0	0
#define R1	1
#define R2	2
#define R3	3
#define C0	4
#define	C1	5
#define	C2	6
#define C3	7

#define keypad_data_pins			PORTD
#define keypad_data_pins_dir		DDRD
#define keypad_input_pins_register	PIND


void keypad_init();
char keypad_GETKEY();


#endif /* KEYPAD_H_ */