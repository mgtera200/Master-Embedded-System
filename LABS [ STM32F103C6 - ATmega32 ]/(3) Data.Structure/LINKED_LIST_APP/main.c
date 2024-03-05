/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *      Author: MOHTERA
 */
#include "lin.h"
int main(){
	char temp_text[40];
	while(1){
		dprintf("\n =================");
		dprintf("\n\t Choose one of the following options: \n");
		dprintf("\n 1: AddStudent");
		dprintf("\n 2: Delete_Student");
		dprintf("\n 3: view_students");
		dprintf("\n 4: Delete_all");
		dprintf("\n 5: GetNth");
		dprintf("\n 6: list length");
		dprintf("\n 7: reverse index");
		dprintf("\n 8: middle node");
		dprintf("\n 9: loop");
		dprintf("\n Enter option Number:");
		gets(temp_text);
		dprintf("\n ==================\n");
		switch(atoi(temp_text)){

		case 1:
			add_student();
			break;
		case 2:
			Delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			Delete_all();
			break;
		case 5:
			GetNth();
			break;
		case 6:
			length();
			break;
		case 7:
			reverse_index();
			break;
		case 8:
			middle();
			break;
		case 9:
			loop();
			break;

		default:
			dprintf("\n wrong option");
			break;
		}


	}

}

