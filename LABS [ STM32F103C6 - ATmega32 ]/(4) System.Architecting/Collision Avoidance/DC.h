/*
 * DC.h
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */

#ifndef DC_H_
#define DC_H_
enum{
	DC_IDLE,
	DC_BUSY
}DC_state_id;
void DC_busy();
extern void (*DC_state)();


#endif /* DC_H_ */
