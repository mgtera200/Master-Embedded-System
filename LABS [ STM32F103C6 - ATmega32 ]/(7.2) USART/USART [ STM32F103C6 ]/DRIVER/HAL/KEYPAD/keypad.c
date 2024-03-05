/*
 * keypad.c
 *
 * ENG.TERA
 */ 
#include "keypad.h"





void keypad_init(){
	Pin_Config_t Pin_config;

	  /* COLUMNS ARE OUTPUTS */

	Pin_config.Pin_Num = 5;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 6;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 7;
	Pin_config.mode = Output_Push_pull;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

//	Pin_config.Pin_Num = 8;
//	Pin_config.mode = Output_Push_pull;
//	Pin_config.Speed_Output = speed_10;
//	MCAL_GPIO_Init(GPIOB, &Pin_config);

	 //ROWS ARE PULL-UP INPUTS

	Pin_config.Pin_Num = 0;
	Pin_config.mode = Input_PullUp;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 1;
	Pin_config.mode = Input_PullUp;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 3;
	Pin_config.mode = Input_PullUp;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);

	Pin_config.Pin_Num = 4;
	Pin_config.mode = Input_PullUp;
	Pin_config.Speed_Output = speed_10;
	MCAL_GPIO_Init(GPIOB, &Pin_config);


	//OUTPUTS ARE PUSHING HIGH VOLT
	MCAL_GPIO_WritePin(GPIOB,C0,1);
	MCAL_GPIO_WritePin(GPIOB,C1,1);
	MCAL_GPIO_WritePin(GPIOB,C2,1);
//	MCAL_GPIO_WritePin(GPIOB,C3,1);


}

char keypad_GETKEY(){
	int keypad_rows[] = { R0, R1, R2, R3 }; //rows of the keypad
	int keypad_Columns[] = { C0, C1, C2 }; //columns


	int i,j;
	for(i=0; i<3; i++)
	{
		//OUTPUT ARE PUSHING HIGH VOLT AS A START
		MCAL_GPIO_WritePin(GPIOB,5,1);
		MCAL_GPIO_WritePin(GPIOB,6,1);
		MCAL_GPIO_WritePin(GPIOB,7,1);
//		MCAL_GPIO_WritePin(GPIOB,8,1);
		// COLUMN[i] is ground
		MCAL_GPIO_WritePin(GPIOB,keypad_Columns[i],0);

		for(j=0; j<4; j++)
		{
			if( MCAL_GPIO_ReadPin(GPIOB, keypad_rows[j]) == 0   )   // Check if key is pressed
			{
				while(   MCAL_GPIO_ReadPin(GPIOB, keypad_rows[j]) == 0     );  // wait for key to be released(single pressing)

				switch(i)
				{

				case 0:{
					if(j==0)
						return '*';
					else if(j==1)
						return '7';
					else if(j==2)
						return '4';
					else if(j==3)
						return '1';
					break;
				}
				case 1:{
					if(j==0)
						return '0';
					else if(j==1)
						return '8';
					else if(j==2)
						return '5';
					else if(j==3)
						return '2';
					break;
				}
				case 2:{
					if(j==0)
						return '#';
					else if(j==1)
						return '9';
					else if(j==2)
						return '6';
					else if(j==3)
						return '3';
					break;
				}
//				case 3:{
//					if(j==0)
//						return '/';
//					else if(j==1)
//						return '*';
//					else if(j==2)
//						return '-';
//					else if(j==3)
//						return '+';
//					break;
//				}

				}
			}
		}
	}
	return 'A'; // Return A if no key is pressed

}


