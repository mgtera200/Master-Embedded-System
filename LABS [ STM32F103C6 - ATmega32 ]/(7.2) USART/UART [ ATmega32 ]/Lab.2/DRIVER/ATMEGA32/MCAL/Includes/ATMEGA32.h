/*
 * ATMEGA32.h
 *
 * Created: 11/30/2023 7:34:22 AM
 *  Author: Dell
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

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

#define UBRRH (*(volatile unsigned char *)(0x0020 + 0x20))
#define UCSRC (*(volatile unsigned char *)(0x0020 + 0x20))
#define UDR	  (*(volatile unsigned char *)(0x0020 + 0x0C))
#define UCSRA (*(volatile unsigned char *)(0x0020 + 0x0B))
#define UCSRB (*(volatile unsigned char *)(0x0020 + 0x0A))
#define UBRRL (*(volatile unsigned char *)(0x0020 + 0x09))





#endif /* ATMEGA32_H_ */