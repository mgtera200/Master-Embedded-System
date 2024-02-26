/*
 * main.c
 *
 * Created: 11/30/2023 7:30:00 AM
 *  Author: Dell
 */ 

#include "ATMEGA32.h"
#include "UART.h"
#include "lcd.h"

int main(void)
{
	unsigned long x;
	LCD_Init();
	UART_Init();
	//UART_Send_Char('a');
	UART_Send_NumberU32(26725); //26725 equivalent decimal number for ?01101000 01100101? which is ascii 'e' then ascii 'h'
    while(1)
    {
	
 	x = UART_Recieve_NumberU16();	// i made it 16 bits just to make it easy testing it on proteus
 								   // when i send e,h characters it prints 26725 (the equivalent ascii)
 	LCD_Display_Number(x);
	    }
}