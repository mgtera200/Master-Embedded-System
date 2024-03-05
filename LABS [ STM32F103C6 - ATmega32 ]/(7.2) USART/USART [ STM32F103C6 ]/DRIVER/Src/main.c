#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/*===============Learn in depth================*/
/*===Second term project Smart Car Barking=====*/
/*Eng.TERA */







#include "STM32F103x8.h"
#include "GPIO_DRIVER.h"
#include <lcd.h>
#include "USART_DRIVER.h"
#include "Servo_Motor.h"
#include "keypad.h"

#define GARBAGE 255
/*=================Global Variables===============*/
uint16_t RFID_CARD_Enter;
uint16_t RFID_CARD_EXIT;

uint8_t pass_entery[3] ={GARBAGE,GARBAGE,GARBAGE};
uint8_t pass_exit[3] ={GARBAGE,GARBAGE,GARBAGE};

uint16_t buff;

unsigned char Available_Slots='3';
uint8_t Search_Done_Entery = 0;
uint8_t Search_Done_Exit = 0;




void RFID_CARD_Enter_CallBack(interrupts_Bits *);
void RFID_CARD_EXIT_CallBack(interrupts_Bits *);

void LCD_Welcome(void);
void LCD_Display_Empty_Slots(void);
void LEDs_Init(void);
void PIRs_Iint(void);
void Store_IDs_From_Admin(void);




int main(void)
{

	GPIOA_CLOCK_EN();
	GPIOB_CLOCK_EN();
	AFIO_CLOCK_EN();
	keypad_init();

	Timer2_init();
	Servo1_Entry_Gate_Init();
	Servo2_Exit_Gate_Init();
	//==========================UART1 INIT=============================
	/* PA9  TX
	 * PA10 RX
	 * PA11 CTC
	 * PA12 RTS
	 */
	USART_Config_t usartCFG;
	usartCFG.Async_EN = USART_Enable;
	usartCFG.Async_Config_s.Baud_Rate = 115200;
	usartCFG.Async_Config_s.Word_Length = Eight_bits;
	usartCFG.Async_Config_s.Parity.Parity_Enable = USART_Disable;
	usartCFG.Async_Config_s.Stop_Bits = Stop_1;
	usartCFG.interrupts_CNFG.RX_Interrupt_Enable_Or_Disable = USART_Enable;
	usartCFG.CallBack_FN = RFID_CARD_Enter_CallBack;
	MCAL_USART_Init(USART1, &usartCFG);
	MCAL_USART_GPIO_Pins_Config(USART1);


	//==========================UART2 INIT=============================
	/* PA2  ->TX
	 * PA3 ->RX
	 * PA0 ->CTS
	 * PA1 ->RTS
	 */

	USART_Config_t usart2CFG;
	usart2CFG.Async_EN = USART_Enable;
	usart2CFG.Async_Config_s.Baud_Rate = 115200;
	usart2CFG.Async_Config_s.Word_Length = Eight_bits;
	usart2CFG.Async_Config_s.Parity.Parity_Enable = USART_Disable;
	usart2CFG.Async_Config_s.Stop_Bits = Stop_1;
	usart2CFG.interrupts_CNFG.RX_Interrupt_Enable_Or_Disable = USART_Enable;
	usart2CFG.CallBack_FN = RFID_CARD_EXIT_CallBack;
	MCAL_USART_Init(USART2, &usart2CFG);
	MCAL_USART_GPIO_Pins_Config(USART2);


	LCD_Init();
	LEDs_Init();
	PIRs_Iint();

	/*==========Enter IDs To Store In Array Pass==========*/
	Store_IDs_From_Admin();

	/*Dash Bord LCD*/
	LCD_Welcome();
	dms(50);
	LCD_Display_Empty_Slots();


	int i=0;
	while(1)
	{
		if(Available_Slots>'0')
		{
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Put your ID in", 1);
			LCD_Goto_XY(3, 0, 1);
			LCD_Send_A_String("Card Reader", 1);

			while(RFID_CARD_Enter == 0 && RFID_CARD_EXIT == 0);

		}
		/*======Parking is full so not allow enetr cars=======*/
		else
		{
			dms(100);
			LCD_Send_Command(0x0c, 1);
			LCD_Send_Command(0x01, 1);
			LCD_Goto_XY(1, 0, 1);
			LCD_Send_A_String("Parking is Full", 1);
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Entry Not", 1);
			LCD_Goto_XY(3, 0, 1);
			LCD_Send_A_String("Allowed", 1);
			while(RFID_CARD_EXIT == 0);
			RFID_CARD_Enter =0;

		}

		//Search about ID in array of Pass
		for(i=0;i<3;i++)
		{
			if(RFID_CARD_Enter == pass_entery[i])
			{
				Search_Done_Entery = 1;
				pass_exit[i] = pass_entery[i];
				pass_entery[i] = GARBAGE;
			}
			else if(RFID_CARD_EXIT == pass_exit[i])
			{
				Search_Done_Exit = 1;
				pass_entery[i] = pass_exit[i];
				pass_exit[i] = GARBAGE;

			}

		}
		/*=====================Enter gate=====================*/
		if((Search_Done_Entery == 1) && (RFID_CARD_Enter != 0) && (Available_Slots > '0'))
		{
			LCD_Send_Command(0x0c, 1);
			LCD_Send_Command(0x01, 1);
			LCD_Goto_XY(1, 0, 1);
			LCD_Send_A_String("ID is Right", 1);
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Entry gate opens", 1);
			MCAL_GPIO_WritePin(GPIOA, 11, 0);
			Servo1_Entry_Gate(UP);
			Available_Slots--;
			RFID_CARD_Enter = 0;
			Search_Done_Entery =0;
			dms(250);
			while(MCAL_GPIO_ReadPin(GPIOA, 7) == 1)
			{
			}
			MCAL_GPIO_WritePin(GPIOA, 11, 1);
			Servo1_Entry_Gate(Down);
			LCD_Welcome();
			dms(250);
			LCD_Display_Empty_Slots();
		}


		/*===================Exit gate====================*/

		if( (Search_Done_Exit == 1) && (RFID_CARD_EXIT != 0) && (Available_Slots < '3'))
		{
			LCD_Send_Command(0x0c, 1);
			LCD_Send_Command(0x01, 1);
			LCD_Goto_XY(1, 0, 1);
			LCD_Send_A_String("ID is Right", 1);
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Exit gate opens", 1);
			MCAL_GPIO_WritePin(GPIOA, 11, 0);
			Servo2_Exit_Gate(UP);
			Available_Slots++;
			RFID_CARD_EXIT = 0;
			Search_Done_Exit =0;
			dms(250);
			while(MCAL_GPIO_ReadPin(GPIOA, 1) == 1)
			{
			}
			MCAL_GPIO_WritePin(GPIOA, 11, 1);
			Servo2_Exit_Gate(Down);
			LCD_Welcome();
			dms(250);
			LCD_Display_Empty_Slots();
		}
		else if(Search_Done_Exit == 1 && RFID_CARD_EXIT != 0 && Available_Slots == '3') {
			LCD_Send_Command(0x0c, 1);
			LCD_Send_Command(0x01, 1);
			LCD_Goto_XY(1, 0, 1);
			LCD_Send_A_String("Parking is ", 1);
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Empty", 1);
			for(i = 0; i<3; i++)
			{
				MCAL_GPIO_TogglePin(GPIOA, 0);
				dms(50);
			}
			MCAL_GPIO_WritePin(GPIOA, 0, 1);
			LCD_Welcome();
			dms(50);
			LCD_Display_Empty_Slots();
			RFID_CARD_EXIT = 0;
			Search_Done_Exit =0;


		}

		/*==================Wrong Id====================*/

		if(( Search_Done_Entery == 0 ||Search_Done_Exit == 0  ) && (RFID_CARD_Enter > 0 || RFID_CARD_EXIT > 0))
		{
			LCD_Send_Command(0x0c, 1);
			LCD_Send_Command(0x01, 1);
			LCD_Goto_XY(1, 0, 1);
			LCD_Send_A_String("Wrong ID", 1);
			LCD_Goto_XY(2, 0, 1);
			LCD_Send_A_String("Try Again", 1);
			for(i = 0; i<3; i++)
			{
				MCAL_GPIO_TogglePin(GPIOA, 0);
				dms(50);
			}
			MCAL_GPIO_WritePin(GPIOA, 0, 1);
			LCD_Welcome();
			dms(50);
			LCD_Display_Empty_Slots();
			RFID_CARD_EXIT = 0;
			RFID_CARD_Enter = 0 ;
		}

	}

	return 0;
}


/*Call Back For UART*/
void RFID_CARD_Enter_CallBack(interrupts_Bits * IRQ)
{
	MCAL_USART_ReceiveChar(USART1, &buff);
	RFID_CARD_Enter = buff;
	MCAL_USART_SendChar(USART1, &buff);
}

void RFID_CARD_EXIT_CallBack(interrupts_Bits * IRQ)
{
	MCAL_USART_ReceiveChar(USART2, &buff);
	RFID_CARD_EXIT = buff;
	MCAL_USART_SendChar(USART2, &buff);
}



void LCD_Welcome(void)
{
	/*Dash Bord LCD*/

	LCD_Send_Command(0x0c, 1);
	LCD_Send_Command(0x01, 1);
	LCD_Goto_XY(1, 0, 1);
	LCD_Send_A_String("Welcome in", 1);
	LCD_Goto_XY(2, 0, 1);
	LCD_Send_A_String("TERA Parking", 1);

}

void LCD_Display_Empty_Slots(void)
{
	LCD_Send_Command(0x0c, 1);
	LCD_Send_Command(0x01, 1);
	LCD_Goto_XY(1, 0, 1);
	LCD_Send_A_String("Empty Slots=", 1);
	LCD_Goto_XY(1, 13, 1);
	LCD_Send_A_Character(Available_Slots, 1);
}

void LEDs_Init(void)
{
	//RED LED A0

	Pin_Config_t pinCFG;

	pinCFG.Pin_Num = 0;
	pinCFG.mode = Output_Open_drain;
	pinCFG.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &pinCFG);

	//GREEN LED A11
	pinCFG.Pin_Num = 11;
	pinCFG.mode = Output_Open_drain;
	pinCFG.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOA, &pinCFG);

	MCAL_GPIO_WritePin(GPIOA, 0, 0); //make A0 ground
	MCAL_GPIO_WritePin(GPIOA, 11, 0); //make A11 ground
	dms(100);
	MCAL_GPIO_WritePin(GPIOA, 0, 1); //make A0 ground
	MCAL_GPIO_WritePin(GPIOA, 11, 1); //make A11 ground
}

void PIRs_Iint(void)
{
	//PIR1 A7
	Pin_Config_t PinCinfg;
	PinCinfg.Pin_Num=7;
	PinCinfg.mode = Input_PullUp;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//PIR2 A1
	PinCinfg.Pin_Num=1;
	PinCinfg.mode = Input_PullUp;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//	MCAL_GPIO_WritePin(GPIOA, 0, 1); //make A0 ground
	//	MCAL_GPIO_WritePin(GPIOA, 11, 1); //make A11 ground

}

void Store_IDs_From_Admin(void)
{
	LCD_Send_Command(0x01, 0);
	LCD_Goto_XY(1, 0, 0);
	LCD_Send_A_String("Enter IDs", 0);
	uint8_t keypad_val,i;
	for(i = 0; i<3; i++ )
	{
		if(i == 0)
		{
			LCD_Goto_XY(2, 0, 0);
			LCD_Send_A_String("First ID:", 0);

		}
		else if(i == 1)
		{
			LCD_Goto_XY(3, 0, 0);
			LCD_Send_A_String("Second ID:", 0);
		}
		else {
			LCD_Goto_XY(4, 0, 0);
			LCD_Send_A_String("Third ID:", 0);
		}
		keypad_val = keypad_GETKEY();
		//Wait for Admin to enter each number in Keypad
		while(keypad_val == 'A')
		{
			keypad_val = keypad_GETKEY();
		}
		pass_entery[i] = keypad_val;
		LCD_Send_A_Character(keypad_val, 0);

	}
	LCD_Send_Command(0x01, 0);
	LCD_Send_A_String("IDs Are Saved ", 0);
	LCD_Goto_XY(2, 0, 0);
	LCD_Send_A_Character(pass_entery[0], 0);
	LCD_Goto_XY(2, 2, 0);
	LCD_Send_A_Character(pass_entery[1], 0);
	LCD_Goto_XY(2, 4, 0);
	LCD_Send_A_Character(pass_entery[2], 0);
	dms(100);



}

