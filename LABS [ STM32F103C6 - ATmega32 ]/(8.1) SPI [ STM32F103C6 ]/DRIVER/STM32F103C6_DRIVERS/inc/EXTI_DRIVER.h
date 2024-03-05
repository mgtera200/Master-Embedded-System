/*
 * GPIO_DRIVER.h
 *
 * ENG-TERA
 */

#ifndef INC_EXTI_DRIVER_H_
#define INC_EXTI_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x8.h"



//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct {

 GPIO_REGISTERS_t* Port;
 uint8_t Pin_num;
 uint8_t IRQ_num;

}EXTI_GPIO_MAPPING_t;

typedef struct {

 EXTI_GPIO_MAPPING_t EXTI_GPIO_Mapping;  // Choose one from @ref EXTI_GPIO depending on what you want
 uint8_t Rising_or_Falling; 			// Must be written as RISING or FALLING or BOTH depending on what you want
 void (* Function_call)(void);


}EXTI_Config_t;


//-----------------------------
//Macros Configuration References
//-----------------------------


// @ref EXTI_GPIO

#define PA0_EXTI0 	 (EXTI_GPIO_MAPPING_t){GPIOA, 0, 6}
#define PB0_EXTI0 	 (EXTI_GPIO_MAPPING_t){GPIOB, 0, 6}
#define PC0_EXTI0 	 (EXTI_GPIO_MAPPING_t){GPIOC, 0, 6}

#define PA1_EXTI1 	 (EXTI_GPIO_MAPPING_t){GPIOA, 1, 7}
#define PB1_EXTI1 	 (EXTI_GPIO_MAPPING_t){GPIOB, 1, 7}
#define PC1_EXTI1 	 (EXTI_GPIO_MAPPING_t){GPIOC, 1, 7}

#define PA2_EXTI2 	 (EXTI_GPIO_MAPPING_t){GPIOA, 2, 8}
#define PB2_EXTI2 	 (EXTI_GPIO_MAPPING_t){GPIOB, 2, 8}
#define PC2_EXTI2 	 (EXTI_GPIO_MAPPING_t){GPIOC, 2, 8}


#define PA3_EXTI3  	 (EXTI_GPIO_MAPPING_t){GPIOA, 3, 9}
#define PB3_EXTI3    (EXTI_GPIO_MAPPING_t){GPIOB, 3, 9}
#define PC3_EXTI3  	 (EXTI_GPIO_MAPPING_t){GPIOC, 3, 9}


#define PA4_EXTI4  	 (EXTI_GPIO_MAPPING_t){GPIOA, 4, 10}
#define PB4_EXTI4 	 (EXTI_GPIO_MAPPING_t){GPIOB, 4, 10}
#define PC4_EXTI4 	 (EXTI_GPIO_MAPPING_t){GPIOC, 4, 10}



#define PA5_EXTI5 	 (EXTI_GPIO_MAPPING_t){GPIOA, 5, 23}
#define PB5_EXTI5 	 (EXTI_GPIO_MAPPING_t){GPIOB, 5, 23}
#define PC5_EXTI5 	 (EXTI_GPIO_MAPPING_t){GPIOC, 5, 23}


#define PA6_EXTI6  	 (EXTI_GPIO_MAPPING_t){GPIOA, 6, 23}
#define PB6_EXTI6 	 (EXTI_GPIO_MAPPING_t){GPIOB, 6, 23}
#define PC6_EXTI6 	 (EXTI_GPIO_MAPPING_t){GPIOC, 6, 23}


#define PA7_EXTI7  	 (EXTI_GPIO_MAPPING_t){GPIOA, 7, 23}
#define PB7_EXTI7 	 (EXTI_GPIO_MAPPING_t){GPIOB, 7, 23}
#define PC7_EXTI7 	 (EXTI_GPIO_MAPPING_t){GPIOC, 7, 23}



#define PA8_EXTI8 	 (EXTI_GPIO_MAPPING_t){GPIOA, 8, 23}
#define PB8_EXTI8 	 (EXTI_GPIO_MAPPING_t){GPIOB, 8, 23}
#define PC8_EXTI8 	 (EXTI_GPIO_MAPPING_t){GPIOC, 8, 23}



#define PA9_EXTI9 	 (EXTI_GPIO_MAPPING_t){GPIOA, 9, 23}
#define PB9_EXTI9 	 (EXTI_GPIO_MAPPING_t){GPIOB, 9, 23}
#define PC9_EXTI9 	 (EXTI_GPIO_MAPPING_t){GPIOC, 9, 23}


#define PA10_EXTI10  (EXTI_GPIO_MAPPING_t){GPIOA, 10, 40}
#define PB10_EXTI10  (EXTI_GPIO_MAPPING_t){GPIOB, 10, 40}
#define PC10_EXTI10  (EXTI_GPIO_MAPPING_t){GPIOC, 10, 40}


#define PA11_EXTI11  (EXTI_GPIO_MAPPING_t){GPIOA, 11, 40}
#define PB11_EXTI11  (EXTI_GPIO_MAPPING_t){GPIOB, 11, 40}
#define PC11_EXTI11  (EXTI_GPIO_MAPPING_t){GPIOC, 11, 40}


#define PA12_EXTI12  (EXTI_GPIO_MAPPING_t){GPIOA, 12, 40}
#define PB12_EXTI12  (EXTI_GPIO_MAPPING_t){GPIOB, 12, 40}
#define PC12_EXTI12  (EXTI_GPIO_MAPPING_t){GPIOC, 12, 40}


#define PA13_EXTI13  (EXTI_GPIO_MAPPING_t){GPIOA, 13, 40}
#define PB13_EXTI13  (EXTI_GPIO_MAPPING_t){GPIOB, 13, 40}
#define PC13_EXTI13  (EXTI_GPIO_MAPPING_t){GPIOC, 13, 40}


#define PA14_EXTI14  (EXTI_GPIO_MAPPING_t){GPIOA, 14, 40}
#define PB14_EXTI14  (EXTI_GPIO_MAPPING_t){GPIOB, 14, 40}
#define PC14_EXTI14  (EXTI_GPIO_MAPPING_t){GPIOC, 14, 40}

#define PA15_EXTI15  (EXTI_GPIO_MAPPING_t){GPIOA, 15, 40}
#define PB15_EXTI15  (EXTI_GPIO_MAPPING_t){GPIOB, 15, 40}
#define PC15_EXTI15  (EXTI_GPIO_MAPPING_t){GPIOC, 15, 40}

// @ref RISING OR FALLING

#define RISING    0
#define FALLING   1
#define BOTH	  2





/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
void MCAL_EXTI_init(EXTI_Config_t*);
void MCAL_EXTI_DeInit(EXTI_Config_t* EXTI_Config_s);
void MCAL_EXTI_Update(EXTI_Config_t*);




#endif /* INC_EXTI_DRIVER_H_ */
