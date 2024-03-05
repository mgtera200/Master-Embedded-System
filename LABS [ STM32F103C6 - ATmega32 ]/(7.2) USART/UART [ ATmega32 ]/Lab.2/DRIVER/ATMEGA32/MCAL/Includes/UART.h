/*
 * UART.h
 *
 * Created: 11/30/2023 7:32:11 AM
 *  Author: Dell
 */ 


#ifndef UART_H_
#define UART_H_

void UART_Init(void);
void UART_Send_Char(unsigned char);
unsigned char UART_Recieve_Char(void);
void UART_Send_NumberU32(unsigned long);
unsigned short UART_Recieve_NumberU16(void);





#endif /* UART_H_ */