/*
 * keypad.c
 *
 * Created: 11/10/2023 9:41:47 PM
 *  Author: Dell
 */ 
#include "keypad.h"



char keypad_Columns[4]={C0,C1,C2,C3};
char keypad_rows[4]={R0,R1,R2,R3};
	
void keypad_init(){
	
	keypad_data_pins_dir |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));     //COLUMNS ARE OUTPUTS
	keypad_data_pins |= ((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));    //ROWS ARE PULL-UP INPUTS
	keypad_data_pins |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));    //OUTPUT ARE SOURCE
}

char keypad_GETKEY(){

int i,j;
for(i=0; i<4; i++)
{
	keypad_data_pins |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));    //OUTPUT ARE SOURCE
	keypad_data_pins &= ~(1<<keypad_Columns[i]);
	for(j=0; j<4; j++)
	{
		if(  ( ( keypad_input_pins_register & (1<<keypad_rows[j]) ) >> keypad_rows[j]   ) == 0   )   // Check if key is pressed
		{
			while(   ( ( keypad_input_pins_register & (1<<keypad_rows[j]) ) >> keypad_rows[j]   ) == 0     );  // wait for key to be released(single pressing)
			
			switch(i)
			{
				
				case 0:{
					if(j==0)
						return '7';
					else if(j==1)
						return '4';
					else if(j==2)
						return '1';
					else if(j==3)
						return '?';
					break;
				}
				case 1:{
					if(j==0)
						return '8';
					else if(j==1)
						return '5';
					else if(j==2)
						return '2';
					else if(j==3)
						return '0';
					break;
				}
				case 2:{
					if(j==0)
						return '9';
					else if(j==1)
						return '6';
					else if(j==2)
						return '3';
					else if(j==3)
						return '=';
					break;
				}
				case 3:{
					if(j==0)
				    	return '/';
					else if(j==1)
						return '*';
					else if(j==2)
						return '-';
					else if(j==3)
						return '+';
					break;
				}				
				
			}
		}
	}
}
	return 'A'; // Return A if no key is pressed

}


