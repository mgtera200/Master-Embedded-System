/*
 * address.h
 *
 * Created: 11/10/2023 1:35:36 AM
 *  Author: Dell
 */ 


#ifndef ADDRESS_H_
#define ADDRESS_H_

#define IO_BASE 0x0020

#define PORTA (*(volatile unsigned char *)(IO_BASE + 0x1B))
#define DDRA (*(volatile unsigned char *)(IO_BASE + 0x1A))
#define PINA (*(volatile unsigned char *)(IO_BASE + 0x19))

#define PORTB (*(volatile unsigned char *)(IO_BASE + 0x18))
#define DDRB (*(volatile unsigned char *)(IO_BASE + 0x17))

#define PORTC (*(volatile unsigned char *)(IO_BASE + 0x15))
#define DDRC (*(volatile unsigned char *)(IO_BASE + 0x14))

#define PORTD (*(volatile unsigned char *)(IO_BASE + 0x12))
#define DDRD (*(volatile unsigned char *)(IO_BASE + 0x11))
#define PIND (*(volatile unsigned char *)(IO_BASE + 0x10))




#endif /* ADDRESS_H_ */