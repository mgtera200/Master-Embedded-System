/*
 * SPI_DRIVER.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Eng.TERA
 */

#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_


//-----------------------------------------
//-------<< INCLUDES >>--------------------
//-----------------------------------------
#include "STM32F103x8.h"

//-----------------------------------------
//-------<< Generic Macros >>--------------
//-----------------------------------------

#define MASTER
//#define SLAVE

//----------------------------------------------------------------
//-------<< User type definitions (structures) >>-----------------
//----------------------------------------------------------------
typedef struct{

	uint8_t Receive_buffer_not_empty_flag :1;
	uint8_t Transmit_buffer_empty_flag :1;
	uint8_t Reserved :6;


}Interrupt_flags_bits_t;
typedef struct{

	uint16_t MASTER_OR_SLAVE;      			//@ref MASTER-SLAVE
	uint16_t SPI_MODES;      				//@ref SPI MODES
	uint16_t clock_polarity;				//@ref CLOCK POLARITY
	uint16_t clock_phase;					//@ref CLOCK PHASE
	uint16_t data_frame;					//@ref DATA FRAME
	uint16_t frame_format;					//@ref FRAME FORMAT
	uint16_t Baud_rate_control;				//@ref BAUD RATE
	uint16_t NSS_Management;				//@ref NSS MANAGEMENT
	uint16_t Tx_buffer_empty_interrupt;		//@ref Interrupts
	uint16_t RX_buffer_not_empty_interrupt;	//@ref NSS MANAGEMENT
	void (*CallBack_PTR)(Interrupt_flags_bits_t *);




}SPI_Config_t;

//----------------------------------------------------------------
//-------<< Macros Configuration References >>--------------------
//----------------------------------------------------------------


//@REF MASTER-SLAVE

#define Master													((uint16_t)1<<2)
#define Slave													((uint16_t)0<<2)

//REF CLOCK POLARITY
#define Clock_high_when_idle									((uint16_t)1<<1)
#define Clock_low_when_idle										((uint16_t)0<<1)

//REF CLOCK PHASE
#define Second_ck_transition_first_data							(uint16_t)1
#define First_ck_transition_first_data							(uint16_t)0

//REF DATA FRAME
#define data_8_bits												((uint16_t)0<<11)
#define data_16_bits											((uint16_t)1<<11)

//REF FRAME FORMAT
#define MSB_transmitted_first									((uint16_t)0<<7)
#define LSB_transmitted_first									((uint16_t)1<<7)



//Hardware
#define SPI_NSS_HARDWARE_SLAVE                        (uint16_t)(0) //SSM bit in SPI_CR1 register
#define SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE     ~(uint16_t)(1<<2) //SSOE bit in SPI_CR2 register
#define SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE      (uint16_t)(1<<2) ///SSOE bit in SPI_CR2 register

//Software
//we control the value of the NSS pin through a bit(SSI) in a register(SPI_CR1)

#define SPI_NSS_SOFTWARE_INTERNAL_SS_RESET            (uint16_t)(1<<9) //SSM bit in SPI_CR1 register (SSI bit is 0)
#define SPI_NSS_SOFTWARE_INTERNAL_SS_SET              (uint16_t)(1<<9 | 1<<8) //(SSM bit | SSI bit) in SPI_CR1 register

//REF SPI MODES
#define SPI_COMM_MODE_2LINES_TX_RX         (uint16_t)(0)
#define SPI_COMM_MODE_2LINES_RX            (uint16_t)(1<<10)
#define SPI_COMM_MODE_1LINE_Receive        (uint16_t)(1<<15)
#define SPI_COMM_MODE_1LINE_Transmit       ((uint16_t)(1<<15 | 1<<14))


//REF INTERRUPTS
#define Interrupt_Enable										(uint16_t)0x1
#define Interrupt_Disable										(uint16_t)0x0

//REF BAUD RATE
#define CLK_DIVIDED_2											((uint16_t)0b000 << 3)
#define CLK_DIVIDED_4											((uint16_t)0b001 << 3)
#define CLK_DIVIDED_8											((uint16_t)0b010 << 3)
#define CLK_DIVIDED_16											((uint16_t)0b011 << 3)
#define CLK_DIVIDED_32											((uint16_t)0b100 << 3)
#define CLK_DIVIDED_64											((uint16_t)0b101 << 3)
#define CLK_DIVIDED_128											((uint16_t)0b110 << 3)
#define CLK_DIVIDED_256											((uint16_t)0b111 << 3)


/*
 * ===============================================
 * APIs Supported by "MCAL SPI DRIVER"
 * ===============================================
 */

void MCAL_SPI_Init(SPI_REGISTERS_t * SPIx,SPI_Config_t * SPI_Config_s);
void MCAL_SPI_Send_Character(SPI_REGISTERS_t * SPIx, uint16_t * buffer);
void MCAL_SPI_Recieve_Character(SPI_REGISTERS_t * SPIx, uint16_t * buffer);
void MCAL_SPI_GPIO_PINS_CONFIG(SPI_REGISTERS_t * SPIx);
void MCAL_SPI_TX_RX(SPI_REGISTERS_t* SPIx, uint16_t* buffer );


#endif /* INC_SPI_DRIVER_H_ */
