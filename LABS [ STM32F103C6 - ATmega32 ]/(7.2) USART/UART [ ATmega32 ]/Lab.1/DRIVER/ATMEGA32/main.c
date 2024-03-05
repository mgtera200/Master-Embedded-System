/*
 * main.c
 *
 * Created: 11/30/2023 7:30:00 AM
 *  Author: Dell
 */ 

#include "ATMEGA32.h"
#include "UART.h"
#include "lcd.h"
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char buff[30];
static unsigned char str[] = "ENG.TERA";
int main(void)
{
	LCD_Init();
	UART_Init();
	//UART_Send_Char('a');
	//UART_Send_NumberU32(26725); //26725 equivalent decimal number for ?01101000 01100101? which is ascii 'e' then ascii 'h'
		int i=0;
		//char x;
	UART_Send_String_when_Interrupt(str);
	UART_Recieve_String_when_Interrupt();


	//UART_Send_String(str);
    while(1)
    {
	
 	//x = UART_Recieve_NumberU16();	// i made it 16 bits just to make it easy testing it on proteus
 								   // when i send e,h characters it prints 26725 (the equivalent ascii)
 	//LCD_Display_Number(x);
	 
// 	 UART_Recieve_String(buff1);
// 	 LCD_Send_String(buff1);

// if((UCSRA & (1<<7)))   //periodic
// {
// 	LCD_gotoXY(2,0);
// 	x = UART_Recieve_Char();
// 	LCD_Send_Character(x);
// 	
// }

	LCD_gotoXY(1,0);
	LCD_Display_Number(i);
	_delay_ms(500);
	i++;
	    }
}

ISR(USART_UDRE_vect){
	static int i=1;
	if(str[i] != '\0'){
		
		UART_Send_Char(str[i]);
		i++;
	}
	else{
		UART_Disable_DR_EMPTY_Interrupt();
	}
}

ISR(USART_RXC_vect)
{
	static int x=0;
	int i;
	buff[x]=UART_Recieve_Char();
	if(buff[x] != '\r'){
		x++;
	}
	else if(buff[x] == '\r'){
		buff[x]='\0';
		LCD_gotoXY(2,0);
		for(i=0; i<x; i++)
		{
			LCD_Send_Character(buff[i]);
		}
		x=0;
	
	}
}
