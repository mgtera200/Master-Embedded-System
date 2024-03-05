/*
 * DoBits.h
 *
 * Created: 10/26/2023 3:08:54 AM
 *  Author: Dell
 */ 


#ifndef DOBITS_H_
#define DOBITS_H_

#define SETBIT(reg,bit) reg |= (1<<bit)
#define CLRBIT(reg,bit) reg &= ~(1<<bit)
#define TOGBIT(reg,bit) reg ^= (1<<bit)






#endif /* DOBITS_H_ */