/*
 * adresse.h
 *
 * Created: 10/26/2023 3:37:23 AM
 *  Author: Dell
 */ 


#ifndef ADRESSE_H_
#define ADRESSE_H_


#define IO_BASE 0x0020

#define PORTA (*(volatile unsigned char *)(IO_BASE + 0x1B))
#define DDRA (*(volatile unsigned char *)(IO_BASE + 0x1A))

#define PORTB (*(volatile unsigned char *)(IO_BASE + 0x18))
#define DDRB (*(volatile unsigned char *)(IO_BASE + 0x17))

#define PORTC (*(volatile unsigned char *)(IO_BASE + 0x15))
#define DDRC (*(volatile unsigned char *)(IO_BASE + 0x14))

#define PORTD (*(volatile unsigned char *)(IO_BASE + 0x12))
#define DDRD (*(volatile unsigned char *)(IO_BASE + 0x11))
#define PIND (*(volatile unsigned char *)(IO_BASE + 0x10))





#endif /* ADRESSE_H_ */