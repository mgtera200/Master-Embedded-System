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
void UART_Send_String(unsigned char * ptr);
void UART_Recieve_String(unsigned char * buff);
void UART_Enable_Tx_Interrupt(void);
void UART_Enable_Rx_Interrupt(void);
void UART_Enable_DR_EMPTY_Interrupt(void);
void UART_Send_String_when_Interrupt(unsigned char * ptr);
void UART_Recieve_String_when_Interrupt(void);
void UART_Disable_DR_EMPTY_Interrupt(void);
void UART_Disable_TX_Interrupt(void);
void UART_Disable_RX_Interrupt(void);













#endif /* UART_H_ */