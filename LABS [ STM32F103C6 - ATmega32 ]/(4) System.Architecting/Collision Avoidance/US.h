/*
 * US.h
 *
 *  Created on: Sep 4, 2023
 *      Author: MOHTERA
 */

#ifndef US_H_
#define US_H_
enum{
	US_BUSY,
}US_STATE_ID;
void US_busy();
extern void (* US_state)();


#endif /* US_H_ */
