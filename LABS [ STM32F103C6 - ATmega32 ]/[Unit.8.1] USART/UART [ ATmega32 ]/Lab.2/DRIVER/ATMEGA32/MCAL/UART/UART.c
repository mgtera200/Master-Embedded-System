/*
 * UART.c
 *
 * Created: 11/30/2023 7:31:05 AM
 *  Author: Dell
 */ 
#include "ATMEGA32.h"


void UART_Init(void){
	
	/* Set baud rate */
	//for baud rate 9600 we should write in UBRR 51 and U2X = 0
	UBRRL = 51;
	/* Enable receiver and transmitter */
	UCSRB |= 0b00011000;
	
	/* Set frame format: 8data, 1stop bit */
	UCSRC |= 0b10000110;
	
}
void UART_Send_Char(unsigned char Data){
	
	while ( !( UCSRA & (1<<5)) );
	UDR = Data;
	
}
unsigned char UART_Recieve_Char(void){
	
	while ( !(UCSRA & (1<<7)) );
	
	return UDR;
	
	
}
void UART_Send_NumberU32(unsigned long Number){
	unsigned char * ptr = &Number;
	UART_Send_Char(ptr[0]);
	UART_Send_Char(ptr[1]);
	UART_Send_Char(ptr[2]);
	UART_Send_Char(ptr[3]);

}

unsigned short UART_Recieve_NumberU16(void){ // i made it 16 bits just to make it easy testing it on proteus
											// when i send e,h characters it prints 26725 (the equivalent ascii)
	unsigned short Number;
	unsigned char * ptr = (unsigned char*)&Number;
	ptr[0] = UART_Recieve_Char();
	ptr[1] = UART_Recieve_Char();
// 	ptr[2] = UART_Recieve_Char();
// 	ptr[3] = UART_Recieve_Char();
	return Number;

}
