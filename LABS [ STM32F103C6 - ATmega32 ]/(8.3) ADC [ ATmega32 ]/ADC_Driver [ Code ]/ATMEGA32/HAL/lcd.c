/*
 * lcd.c
 *
 * Created: 12/2/2023 3:32:49 AM
 *  Author: Dell
 */ 

#include "lcd.h"

void LCD_Kick(void){
	LCD_CONTROL_PINS &= ~(1<<EN_PIN);
	_delay_ms(50);
	LCD_CONTROL_PINS |= (1<<EN_PIN);
}

void LCD_Check_Is_Busy(void){
	LCD_Data_Pins_Dir = 0; //  Configure Data pins as an inputs
	LCD_CONTROL_PINS |= (1<<RW_PIN); // Read mode
	LCD_CONTROL_PINS &= ~(1<<RS_PIN); // Instruction register is on
	LCD_Kick();
	
	#ifdef FOUR_BIT_MODE
	if(((LCD_Data_Read & (1 << DB7_PIN)) >> DB7_PIN)==1)//if busy
	{
		LCD_Kick();
		_delay_ms(1);
		LCD_Check_Is_Busy();//check if busy again till its not busy (recursion)
	}
	LCD_Kick();
	#endif

	
	#ifdef EIGHT_BIT_MODE
	if(((LCD_Data_Read & (1 << DB7_PIN)) >> DB7_PIN)==1)//if busy
	{
		_delay_ms(1);
		LCD_Check_Is_Busy();//check if busy again till its not busy (recursion)
	}
	#endif
	
	LCD_Data_Pins_Dir = 0xFF;// Configure Data pins as an outputs
	LCD_CONTROL_PINS &= ~(1<<RW_PIN); // Write mode

}
void LCD_Send_Command(unsigned char command){
	LCD_Check_Is_Busy();
	LCD_CONTROL_PINS &= ~(1<<RS_PIN); // Instruction register is on
	
	#ifdef EIGHT_BIT_MODE
	LCD_Data_Pins = command;
	LCD_Kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_Data_Pins = (LCD_Data_Pins & 0x0F) | (command & 0xF0);
	LCD_Kick();
	LCD_Check_Is_Busy();
	LCD_Data_Pins = (LCD_Data_Pins & 0x0F) | (command<<4);
	LCD_Kick();
	#endif
}
void LCD_SEND_A_Command_4mode(unsigned char command){
	LCD_Check_Is_Busy();
	LCD_Data_Pins &= 0x0F;
	LCD_Data_Pins |= (command&0xF0);
	LCD_CONTROL_PINS &= ~((1<<RW_PIN)|(1<<RS_PIN));
	LCD_Kick();
	LCD_CONTROL_PINS &= 0x0F;
	LCD_CONTROL_PINS |= ((command<<4)&0xF0);
	LCD_Kick();
}
void LCD_Send_Character(unsigned char character){
	
	LCD_Check_Is_Busy();
	LCD_CONTROL_PINS |= (1<<RS_PIN); // Data register is on
	#ifdef EIGHT_BIT_MODE
	LCD_Data_Pins = character;
	LCD_Kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_Data_Pins = (LCD_Data_Pins & 0x0F) | (character & 0xF0);
	LCD_CONTROL_PINS |= (1 << RS_PIN); // 1: Data Register
	LCD_CONTROL_PINS &= ~(1 << RW_PIN); // 0: Write
	LCD_Kick();

	LCD_Check_Is_Busy();
	LCD_Data_Pins = (LCD_Data_Pins & 0x0F) | (character << 4);
	LCD_CONTROL_PINS |= (1 << RS_PIN); // 1: Data Register
	LCD_CONTROL_PINS &= ~(1 << RW_PIN); // 0: Write
	LCD_Kick();
	#endif
}

void LCD_Clear_Screen(void){
	
	#ifdef FOUR_BIT_MODE
	LCD_SEND_A_Command_4mode(LCD_CLEAR);
	#endif
	
	#ifdef EIGHT_BIT_MODE
	LCD_Send_Command(LCD_CLEAR);
	#endif
}

void LCD_Init(void){
	
	LCD_CONTROL_PINS_Dir |= ((1<<EN_PIN) | (1<<RW_PIN) | (1<<RS_PIN)); // Configure Control pins as an outputs
	LCD_Data_Pins_Dir = 0xFF; // Configure Data pins as an outputs
	LCD_Clear_Screen();
	
	#ifdef FOUR_BIT_MODE
	LCD_SEND_A_Command_4mode(0x02);
	LCD_SEND_A_Command_4mode(LCD_FUNCTION_4BIT_2LINES);
	LCD_SEND_A_Command_4mode(LCD_ENTRY_MODE);
	LCD_SEND_A_Command_4mode(LCD_BEGIN_AT_FIRST_ROW);
	LCD_SEND_A_Command_4mode(LCD_DISP_ON_CURSOR_BLINK);

	#endif
	
	#ifdef EIGHT_BIT_MODE
	LCD_Send_Command(LCD_FUNCTION_8BIT_2LINES);
	LCD_Send_Command(LCD_ENTRY_MODE);
	LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Send_Command(LCD_DISP_ON_CURSOR_BLINK);

	#endif

}
void LCD_Send_String(const unsigned char* string){
	
	int count =0;
	while(1){
		if(count == 16)//First line end reached
		{
			LCD_Send_Command(LCD_BEGIN_AT_SECOND_ROW);
		}
		if(count == 32)//Second line end reached
		{
			LCD_Clear_Screen();
			LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
			count=0;
		}
		LCD_Send_Character(*string);
		string++;
		count++;
		if(*string == '\0')//End of the string reached
		{
			break;//stop
		}
	}
}
void LCD_Display_Number(unsigned short Number){
	
	char str[20];
	sprintf(str,"%u",Number);//Converting integer to string
	LCD_Send_String(str);

}
void LCD_Display_Real_Number(float_t Number){
	char str[20];
	sprintf(str,"%.3f",Number);//Converting integer to string
	LCD_Send_String(str);
}

void LCD_gotoXY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_Send_Command(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}