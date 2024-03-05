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

void UART_Send_String(unsigned char * ptr){
	int i=0;
	do{
		UART_Send_Char(ptr[i]);
		i++;
	}while(ptr[i] != '\0');
}

void UART_Recieve_String(unsigned char * buff){
	int i=0;
	buff[i]=UART_Recieve_Char();
	
	while(buff[i] != '\r'){
		i++;
		buff[i]=UART_Recieve_Char();
	}
	buff[i]='\0';
	
}

void UART_Enable_Tx_Interrupt(void){
	SREG |= (1<<7);
	UCSRB |= (1<<6);
}
void UART_Enable_Rx_Interrupt(void){
	SREG |= (1<<7);
	UCSRB |= (1<<7);
	
}
void UART_Enable_DR_EMPTY_Interrupt(void){
	SREG |= (1<<7);
	UCSRB |= (1<<5);
}
void UART_Send_String_when_Interrupt(unsigned char * ptr){
	
	int i=0;
	UART_Send_Char(ptr[i]);
	UART_Enable_DR_EMPTY_Interrupt();

}
void UART_Disable_DR_EMPTY_Interrupt(void){
SREG &= ~(1<<7);
UCSRB &= ~(1<<5);
}

void UART_Recieve_String_when_Interrupt(void){
	
	UART_Enable_Rx_Interrupt();
	
}

void UART_Disable_TX_Interrupt(void){
	SREG &= ~(1<<7);
	UCSRB &= ~(1<<6);
}

void UART_Disable_RX_Interrupt(void){
	SREG &= ~(1<<7);
	UCSRB &= ~(1<<7);
}
