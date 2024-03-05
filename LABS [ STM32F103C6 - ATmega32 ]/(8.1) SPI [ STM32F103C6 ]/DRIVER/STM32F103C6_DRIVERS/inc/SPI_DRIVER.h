/*
 *
 *      Author: Eng.TERA
 */


#ifndef INC_STM32F103x8_SPI_DRIVER_H_
#define INC_STM32F103x8_SPI_DRIVER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include <STM32F103x8.h>

#include "GPIO_DRIVER.h"
//-------------------------------------------------
// SPI CONFIGURATION STRUCTURES
//-------------------------------------------------

typedef struct
{
	uint8_t TXE:1; //TX buffer empty interrupt
	uint8_t RXNE:1; //RX buffer not empty interrupt
	uint8_t ERRI:1; //error interrupt
	uint8_t Reserved:1;

}S_IRQ_SRC;


typedef struct
{
	uint16_t	DEVICE_MODE;	// Specifies the SPI operating mode
					// This parameter must be set by @ref SPI_DEVICE_MODE_DEFINE

	uint16_t	COMM_MODE;	// Specifies the SPI bidirectional mode state
					// This parameter must be set by @ref SPI_COMM_MODE_DEFINE

	uint16_t	FRAME_FORMAT;	// Specifies LSB or MSB .
					// This parameter must be set by @ref SPI_FRAME_FORMAT_DEFINE

	uint16_t	DATA_SZ;
					// This parameter must be set by @ref SPI_DATA_SIZE_DEFINE

	uint16_t	CLK_POLARITY;
					// This parameter must be set by @ref SPI_CLKPOLARITY_DEFINE

	uint16_t	CLK_PHASE;
					// This parameter must be set by @ref SPI_CLKPHASE_DEFINE

	uint16_t	NSS;	        // Specifies wether the NSS signal is managed by HW or by SW using the SSI bit enable
					// This parameter must be set by @ref SPI_NSS

	uint16_t	SPI_BAUDRATE_PRESCALAR; //Specifies the baud rate prescalar value which will be used to configure the transmit and recieve SCK clock
						// This parameter must be set by @ref SPI_BAUDRATE_PRESCALAR

	uint16_t	IRQ_ENABLE;
						// This parameter must be set by @ref SPI_IRQ_ENABLE

	void (* P_SPI_IRQ_CALLBACK)(S_IRQ_SRC x);	// Set the c function which will be called once the IRQ occurs

}SPI_Config_t;



//-------------------------------------------------
// MACROS
//-------------------------------------------------

//@ref SPI_DEVICE_MODE_DEFINE
#define SPI_DEVICE_MODE_SLAVE			(0x00000000U)
#define SPI_DEVICE_MODE_MASTER			 (uint32_t)(0x1U<<2) //CR1 MSTR:1



//@ref SPI_COMM_MODE_DEFINE
#define SPI_DIRECTION_2LINES				(uint16_t)(0)
#define SPI_DIRECTION_2LINES_RXONLY			(uint16_t)(0x1U<<10) //CR1 RXONLY:1 receive only
#define SPI_DIRECTION_1LINE_RECEIVE_ONLY	(uint16_t)(0x1U<<15) //CR1 BIDIMODE:1 bidirectional data mode enable
#define SPI_DIRECTION_1LINE_TRANSMIT_ONLY	(uint16_t)((0x1U<<15)|(0x1U<<14)) //CR1 bit 15 is bidimode: 1 line Bidirectional data mode enable & bit 14 BIDIOE: Output enable (Transmit only)



//@ref SPI_FRAME_FORMAT_DEFINE
#define SPI_FRAME_FORMAT_MSB 				 (uint16_t)(0)
#define SPI_FRAME_FORMAT_LSB 				 (uint16_t)(0x1U<<7)

/*Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted first*/



//@ref SPI_DATA_SIZE_DEFINE
#define SPI_DATA_SIZE_8B 				 (uint16_t)(0)
#define SPI_DATA_SIZE_16B  				 (1<<11)

/*Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception
Note: This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation.
It is not used in I2S mode*/



//@ref SPI_CLKPOLARITY_DEFINE

#define SPI_CLKPOLARITY_LOW_WHEN_IDLE			 (uint16_t)(0)
#define SPI_CLKPOLARITY_HIGH_WHEN_IDLE 			 (1<<1) //CR1 bit 1 CPOL selected



//@ref SPI_CLKPHASE_DEFINE

#define SPI_CLKPHASE_1EDGE_FIRST_DATA_CAPTURE_EDGE	 (uint16_t)(0x00000000U)
#define SPI_CLKPHASE_2EDGE_FIRST_DATA_CAPTURE_EDGE 	 (1<<0) //CR1 bit 1 CPHA selected




//@ref SPI_NSS (SPI SLAVE SELECT MANAGEMENT) HW OR SW
//HW
#define SPI_NSS_HW_SLAVE				 (uint16_t)(0)
#define SPI_NSS_HW_MASTER_SSO_ENABLE	 (1<<2)//CR2
#define SPI_NSS_HW_MASTER_SSO_DISABLE	~(1<<2)  //CR2

//SW (Master or slave)
#define SPI_NSS_SW_InternalSoft_Reset 			(0x1U<<9)
#define SPI_NSS_SW_InternalSoft_set 			(1<<9)|(1<<8)
//Bit 9 SSM: Software slave management
//When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
//0: Software slave management disabled
//1: Software slave management enabled
//CR1 Bit 8 SSI: Internal slave select
//This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
//NSS pin and the IO value of the NSS pin is ignored.



//@ref SPI_BAUDRATE_PRESCALAR

/*Bits 5:3 BR[2:0]: Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256
Note: These bits should not be changed when communication is ongoing.
They are not used in I2S mode.*/

#define SPI_BAUDRATE_PRESCALAR_2			(0x00000000U)
#define SPI_BAUDRATE_PRESCALAR_4			(0b001<<3)
#define SPI_BAUDRATE_PRESCALAR_8			(uint32_t)(2<<3)
#define SPI_BAUDRATE_PRESCALAR_16			(0b011<<3)
#define SPI_BAUDRATE_PRESCALAR_32			(0b100<<3)
#define SPI_BAUDRATE_PRESCALAR_64			(0b101<<3)
#define SPI_BAUDRATE_PRESCALAR_128			(0b110<<3)
#define SPI_BAUDRATE_PRESCALAR_256			(0b111<<3)



//@ref SPI_IRQ_ENABLE
#define SPI_IRQ_ENABLE_NONE				(0x00000000U)
#define SPI_IRQ_ENABLE_TXIE				(0x1U<<7) //Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_ENABLE_RXNEIE			(uint32_t)(1<<6) //Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_ENABLE_ERRIE				(0x1U<<5) //Bit 5 ERRIE: Error interrupt enable




typedef enum{
	Polling_enable,
	Polling_disable
}Polling_Mechanism;

//-------------------------------------------------
// APIs supported by "MCAL SPI DRIVER"
//-------------------------------------------------

void MCAL_SPI_INIT (SPI_REGISTERS_t* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeINIT (SPI_REGISTERS_t* SPIx);

void MCAL_SPI_GPIO_SET_PINS(SPI_REGISTERS_t* SPIx);

void MCAL_SPI_SEND_DATA (SPI_REGISTERS_t* SPIx, uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn);
void MCAL_SPI_RECEIVE_DATA (SPI_REGISTERS_t* SPIx, uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn);

void MCAL_SPI_TX_RX (SPI_REGISTERS_t* SPIx,uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn);

#endif
