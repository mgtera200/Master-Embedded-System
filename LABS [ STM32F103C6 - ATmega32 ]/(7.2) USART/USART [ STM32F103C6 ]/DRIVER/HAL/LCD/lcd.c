/*
 * LCD.c
 *
 * Eng.TERA
 */

#include <lcd.h>

uint16_t RS[2]={RS1,RS2}, EN[2]={EN1,EN2};
GPIO_REGISTERS_t* LCD_PORT[2] = {LCD1_PORT,LCD2_PORT};
//vuint32_t* LCD_DATA[2] = {LCD1_DATA,LCD2_DATA};

void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i = 0; i<time; i++)
		for(j=0; j<255; j++);
}

/* NOTE: if index = 0 -> ADMIN LCD , if index =  1	ENTRY LCD */

void LCD_Kick(int index){
	MCAL_GPIO_WritePin(LCD_PORT[index],EN[index],GPIO_PIN_SET);
	wait_ms(10);
	MCAL_GPIO_WritePin(LCD_PORT[index],EN[index],GPIO_PIN_RESET);
}

void LCD_Send_Command (unsigned char CMD,int index){
	//turn RS off for command mode.
	MCAL_GPIO_WritePin(LCD_PORT[index],RS[index],GPIO_PIN_RESET);

#ifdef Eight_Bit_MODE
	//Write the command on D0...D7
	LCD_DATA = (LCD_DATA[index] & 0xff00) | CMD;
	LCD_Kick();
#endif

#ifdef FOUR_Bit_MODE
	//Write the command on D4..D7 first
	MCAL_GPIO_WritePin(LCD_PORT[index], D4, Read_Bit(CMD,4));
	MCAL_GPIO_WritePin(LCD_PORT[index], D5, Read_Bit(CMD,5));
	MCAL_GPIO_WritePin(LCD_PORT[index], D6, Read_Bit(CMD,6));
	MCAL_GPIO_WritePin(LCD_PORT[index], D7, Read_Bit(CMD,7));
	LCD_Kick(index);
	//Write the command on D0..D3
	MCAL_GPIO_WritePin(LCD_PORT[index], D4, Read_Bit(CMD,0));
	MCAL_GPIO_WritePin(LCD_PORT[index], D5, Read_Bit(CMD,1));
	MCAL_GPIO_WritePin(LCD_PORT[index], D6, Read_Bit(CMD,2));
	MCAL_GPIO_WritePin(LCD_PORT[index], D7, Read_Bit(CMD,3));
	LCD_Kick(index);
#endif
}

void LCD_Init(){

	//First Loop initialize ADMIN LCD and The Second initialize ENTRY LCD
	for(int j=0; j<2; j++){
		wait_ms(20);
		//set the control port direction as output so you can send commands to the LCD.
		Pin_Config_t Pincfg;

		//RS OUTPUT Push-Pull
		Pincfg.Pin_Num = RS[j];
		Pincfg.mode = Output_Push_pull;
		Pincfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(LCD_PORT[j],&Pincfg);

		//EN OUTPUT Push-Pull
		Pincfg.Pin_Num = EN[j];
		Pincfg.mode = Output_Push_pull;
		Pincfg.Speed_Output = speed_10;
		MCAL_GPIO_Init(LCD_PORT[j],&Pincfg);

		//turn off enable
		MCAL_GPIO_WritePin(LCD_PORT[j],EN[j],GPIO_PIN_RESET);

#ifdef Eight_Bit_MODE
		//set the port direction as output so you can send information to the LCD.
		uint16_t pin[8]={D0,D1,D2,D3,D4,D5,D6,D7};
		int i;
		for(i=0; i<8; i++){
			Pincfg.Pin_Num = pin[i];
			Pincfg.mode = Output_Push_pull;
			Pincfg.Speed_Output = speed_10;
			MCAL_GPIO_Init(LCD_PORT[i],&Pincfg);
		}
		LCD_Send_Command(LCD_8bit_4Line);
#endif

#ifdef FOUR_Bit_MODE
		//set the MSB port direction as output so you can send information to the LCD.
		uint16_t pin[4]={D4,D5,D6,D7};

		for(int i=0; i<4; i++){
			Pincfg.Pin_Num = pin[i];
			Pincfg.mode = Output_Push_pull;
			Pincfg.Speed_Output = speed_10;
			MCAL_GPIO_Init(LCD_PORT[j],&Pincfg);
		}
		LCD_Send_Command(0x02,j);
		LCD_Send_Command(LCD_4bit_4_Line,j);
#endif

		LCD_Send_Command(LCD_Entry_Mode,j);
		LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line,j);
		LCD_Send_Command(LCD_Display_Cursor_Blinking,j);
	}
}
void LCD_Send_A_Character (char data,int index){
	//turn RS ON for Data mode.
	MCAL_GPIO_WritePin(LCD_PORT[index],RS[index],GPIO_PIN_SET);

#ifdef Eight_Bit_MODE
	//write data on D0...D7
	LCD_DATA = (LCD_DATA[index] & 0xff00) | data;
	LCD_Kick();
#endif

#ifdef FOUR_Bit_MODE
	//send D4..D7 first
	MCAL_GPIO_WritePin(LCD_PORT[index], D4, Read_Bit(data,4));
	MCAL_GPIO_WritePin(LCD_PORT[index], D5, Read_Bit(data,5));
	MCAL_GPIO_WritePin(LCD_PORT[index], D6, Read_Bit(data,6));
	MCAL_GPIO_WritePin(LCD_PORT[index], D7, Read_Bit(data,7));
	LCD_Kick(index);
	//send data D0..D3
	MCAL_GPIO_WritePin(LCD_PORT[index], D4, Read_Bit(data,0));
	MCAL_GPIO_WritePin(LCD_PORT[index], D5, Read_Bit(data,1));
	MCAL_GPIO_WritePin(LCD_PORT[index], D6, Read_Bit(data,2));
	MCAL_GPIO_WritePin(LCD_PORT[index], D7, Read_Bit(data,3));
	LCD_Kick(index);
#endif
}

void LCD_Clear_Screen(int index){
	wait_ms(10);
	LCD_Send_Command(LCD_Clear_Display,index);
}

void LCD_Goto_XY(unsigned char line,unsigned char position,int index){
	if (line == 1)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line + position,index);
	else if(line == 2)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_Second_Line + position,index);
	else if(line == 3)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_Third_Line + position,index);
	else if(line == 4)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_Fourth_Line + position,index);
}

void LCD_Send_A_String(char* str,int index){
	char count = 0;
	while(*str != 0){
		LCD_Send_A_Character(*str++,index);
		count++;
		//Line 1 is complete
		if (count == 16){
			//Go to the second line
			LCD_Goto_XY(2,0,index);
		}
		//Line 2 is complete
		else if(count == 32){
			//Go to the third line
			LCD_Goto_XY(3,0,index);
		}
		//Line 3 is complete
		else if(count == 48){
			//Go to the fourth line
			LCD_Goto_XY(4,0,index);
		}
		//Line 4 is complete
		else if(count == 64){
			//Clear the display and go back to line one
			LCD_Clear_Screen(index);
			LCD_Goto_XY(1,0,index);
			count = 0;
		}
	}
}
