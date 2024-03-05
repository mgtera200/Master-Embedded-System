/*
 * UART_DRIVER.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Eng.TERA
 */


#ifndef INC_USART_DRIVER_H_
#define INC_USART_DRIVER_H_


//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------

#include "STM32F103x8.h"
#include "RCC_DRIVER.h"
#include "GPIO_DRIVER.h"


//----------------------------------------------------------------
//-------<< User type definitions (structures) >>-----------------
//----------------------------------------------------------------

typedef struct{

	uint8_t Parity_Enable;
	uint8_t Parity_Even_Odd;

}Parity_t;

typedef struct{

	//todo


}Sync_t;

typedef struct{

	uint8_t  Word_Length;					// Must be one of @ref definitions
	uint8_t  Stop_Bits;						// Must be one of @ref definitions
	uint32_t Baud_Rate;
	Parity_t Parity;						//Must be one of @ref definitions


}Async_t;
typedef struct{

	uint8_t TX_Interrupt_Enable_Or_Disable;		  // Write "Enable" to enable
	uint8_t RX_Interrupt_Enable_Or_Disable;	   	 // Write "Enable" to enable
	uint8_t TC_Interrupt_Enable_Or_Disable;		// Write "Enable" to enable

}Interrupt_CNFG_t;

typedef struct {
	uint8_t RX_Interrupt:1;
	uint8_t TC_Interrupt:1;
	uint8_t TX_Interrupt:1;
	uint8_t RESERVED:5;

}interrupts_Bits;

typedef struct {
	uint8_t Async_EN;					// Write "Enable" to enable
	uint8_t Sync_EN; 					// Write "Enable" to enable
	Sync_t  Sync_Config_s;
	Async_t Async_Config_s;
	Interrupt_CNFG_t interrupts_CNFG;

	void (* CallBack_FN)(interrupts_Bits *);

}USART_Config_t;

//----------------------------------------------------------------
//-------<< Macros Configuration References >>--------------------
//----------------------------------------------------------------

#define USART_Enable							1
#define USART_Disable							0


//@ref Data bits

#define Eight_bits 						(0<<12)
#define Nine_bits 						(1<<12)

//@ref Stop bits

#define Stop_1							(0x0<<12)
#define Stop_half						(0x1<<12)
#define Stop_2							(0x2<<12)
#define Stop_1_and_half					(0x3<<12)

//@ref Even or Odd parity

#define Even							(0<<9)
#define Odd								(1<<9)


/*
 * ===============================================
 * APIs Supported by "MCAL USART DRIVER"
 * ===============================================
 */
void    MCAL_USART_Init(USART_REGISTERS_t * USARTx,USART_Config_t * USART_Config_s);
void    MCAL_USART_Deinit(USART_REGISTERS_t * USARTx);
void	MCAL_USART_ReceiveChar(USART_REGISTERS_t * USARTx,uint16_t * Buffer);
void    MCAL_USART_SendChar(USART_REGISTERS_t * USARTx,uint16_t * Buffer);
void 	MCAL_USART_GPIO_Pins_Config(USART_REGISTERS_t * USARTx);


#endif /* INC_USART_DRIVER_H_ */
