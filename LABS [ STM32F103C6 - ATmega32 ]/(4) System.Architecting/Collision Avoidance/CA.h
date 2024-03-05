/*
 * CA.H
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */

#ifndef CA_H_
#define CA_H_
#include "stdio.h"
#include "stdlib.h"
enum {
	CA_WAITING,
	CA_DRIVING
}CA_STATE_ID;
void CA_waiting();
void CA_driving();
extern void (*CA_state)();
#endif /* CA_H_ */
