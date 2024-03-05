/*
 * STM32F103xx.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Dell
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_
//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

//=======================================================================//

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_MEMORY	 0x08000000UL
#define SRAM_MEMORY		 0x20000000UL
#define SYSTEM_MEMORY    0x1FFFF000UL

//=======================================================================//


//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------
#define GPIOA_BASE		0x40010800UL
#define GPIOB_BASE		0x40010C00UL
#define GPIOC_BASE		0x40011000UL
#define GPIOD_BASE		0x40011400UL
#define GPIOE_BASE		0x40011800UL
#define AFIO_BASE		0x40010000UL
#define RCC_BASE		0x40021000UL
#define EXTI_BASE		0x40010400UL
#define NVIC_BASE		0xE000E100UL
#define NVIC_ICER_BASE	0xE000E180UL
#define USART1_BASE		0x40013800UL
#define USART2_BASE		0x40004400UL
#define USART3_BASE		0x40004800UL
#define SPI1_BASE		0x40013000UL
#define SPI2_BASE		0x40003800UL
#define I2C1_BASE		0x40005400UL
#define I2C2_BASE		0x40005800UL








//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t GPIOx_CRL;
	volatile uint32_t GPIOx_CRH;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_BRR;
	volatile uint32_t GPIOx_LCKR;

}GPIO_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;


}RCC_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR[4];
	volatile uint32_t RESERVED0;
	volatile uint32_t AFIO_MAPR2;

}AFIO_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;

}EXTI_REGISTERS_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: NVIC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t NVIC_ISER0;
	volatile uint32_t NVIC_ISER1;
	volatile uint32_t NVIC_ISER2;


}NVIC_REGISTERS_t;

typedef struct{

	volatile uint32_t NVIC_ICER0;
	volatile uint32_t NVIC_ICER1;
	volatile uint32_t NVIC_ICER2;


}NVIC_ICER_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: UART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;



}USART_REGISTERS_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint16_t SPI_DR;

}SPI_REGISTERS_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers: I2C
//-*-*-*-*-*-*-*-*-*-*-*


typedef struct{

	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;

}I2C_REGISTERS_t;



//=======================================================================//

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA						((GPIO_REGISTERS_t *)GPIOA_BASE)
#define GPIOB						((GPIO_REGISTERS_t *)GPIOB_BASE)
#define GPIOC						((GPIO_REGISTERS_t *)GPIOC_BASE)
#define GPIOD						((GPIO_REGISTERS_t *)GPIOD_BASE)
#define GPIOE						((GPIO_REGISTERS_t *)GPIOE_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO						((AFIO_REGISTERS_t *)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC							((RCC_REGISTERS_t *)RCC_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*


#define EXTI						((EXTI_REGISTERS_t *)EXTI_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: NVIC
//-*-*-*-*-*-*-*-*-*-*-*

#define NVIC						((NVIC_REGISTERS_t *)NVIC_BASE)
#define NVIC_ICER					((NVIC_ICER_REGISTERS_t *)NVIC_ICER_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: UART
//-*-*-*-*-*-*-*-*-*-*-*

#define USART1						((USART_REGISTERS_t *)USART1_BASE)
#define USART2						((USART_REGISTERS_t *)USART2_BASE)
#define USART3						((USART_REGISTERS_t *)USART3_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: SPI
//-*-*-*-*-*-*-*-*-*-*-*

#define SPI1						((SPI_REGISTERS_t *)SPI1_BASE)
#define SPI2						((SPI_REGISTERS_t *)SPI2_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: I2C
//-*-*-*-*-*-*-*-*-*-*-*
#define I2C1						((I2C_REGISTERS_t *)I2C1_BASE)
#define I2C2						((I2C_REGISTERS_t *)I2C2_BASE)

//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//Interrupt Vector Table:
//-*-*-*-*-*-*-*-*-*-*-*

#define I2C1_EV_IRQ				31
#define I2C1_ER_IRQ				32
#define I2C2_EV_IRQ				33
#define I2C2_ER_IRQ				34


//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ Enable\Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//ENABLE

#define	NVIC_IRQ31_I2C1_EV_Enable				(NVIC->NVIC_ISER0 |= 1<<(I2C1_EV_IRQ ))
#define NVIC_IRQ32_I2C1_ER_Enable				(NVIC->NVIC_ISER1 |= 1<<(I2C1_ER_IRQ - 32 ))
#define NVIC_IRQ31_I2C2_EV_Enable				(NVIC->NVIC_ISER1 |= 1<<(I2C2_EV_IRQ - 32 ))
#define NVIC_IRQ32_I2C2_ER_Enable				(NVIC->NVIC_ISER1 |= 1<<(I2C2_ER_IRQ - 32 ))

//DISABLE

#define	NVIC_IRQ31_I2C1_EV_Disable				(NVIC_ICER->NVIC_ICER0 |= 1<<(I2C1_EV_IRQ ))
#define NVIC_IRQ32_I2C1_ER_Disable				(NVIC_ICER->NVIC_ICER1 |= 1<<(I2C1_ER_IRQ - 32 ))
#define NVIC_IRQ31_I2C2_EV_Disable				(NVIC_ICER->NVIC_ICER1 |= 1<<(I2C2_EV_IRQ - 32 ))
#define NVIC_IRQ32_I2C2_ER_Disable				(NVIC_ICER->NVIC_ICER1 |= 1<<(I2C2_ER_IRQ - 32 ))


//-----------------------------------------
//-------<< Bit definitions >>-------------
//-----------------------------------------


/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */



//=======================================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<2)
#define GPIOB_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<3)
#define GPIOC_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<4)
#define GPIOD_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<5)
#define GPIOE_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<6)

#define AFIO_CLOCK_EN()				RCC->RCC_APB2ENR |= (1<<0)

#define USART1_CLOCK_EN()			RCC->RCC_APB2ENR |= (1<<14)
#define USART2_CLOCK_EN()			RCC->RCC_APB1ENR |= (1<<17)
#define USART3_CLOCK_EN()			RCC->RCC_APB1ENR |= (1<<18)

#define SPI1_CLOCK_EN()				RCC->RCC_APB2ENR |= (1<<12)
#define SPI2_CLOCK_EN()				RCC->RCC_APB1ENR |= (1<<14)

#define I2C1_CLOCK_EN()				RCC->RCC_APB1ENR |= (1<<21)
#define I2C2_CLOCK_EN()				RCC->RCC_APB1ENR |= (1<<22)


//-*-*-*-*-*-*-*-*-*-*-*-
//clock disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define I2C1_CLOCK_Reset()			RCC->RCC_APB1RSTR |= (1<<21)
#define I2C2_CLOCK_Reset()			RCC->RCC_APB1RSTR |= (1<<22)


#define SPI1_CLOCK_Reset()			RCC->RCC_APB1RSTR |= (1<<12)
#define SPI2_CLOCK_Reset()			RCC->RCC_APB1RSTR |= (1<<14)







//=======================================================================//

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


#endif /* INC_STM32F103X8_H_ */
