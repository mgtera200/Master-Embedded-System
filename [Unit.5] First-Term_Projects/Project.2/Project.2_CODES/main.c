/*
 * main.c
 *
 *  Created on: Sep 27, 2023
 *      Author: dell
 */
#include "studentbase.h"

int main()
{
	int option;

sinfo buff[50];
fifo sfifo;

	if((Fifo_init(&sfifo ,buff))==queue_no_error){
	//Super Loop
	while(1)
	{
		DPRINTF("\n=========================================\n");
		DPRINTF("Welcome to the Student Management System");
		DPRINTF("\n=========================================\n");

		DPRINTF("1. Add the student Details Manually\n");
		DPRINTF("2. Add the student Details From Text File\n");
		DPRINTF("3. Find the Student Details by Roll Number\n");
		DPRINTF("4. Find the Student Details by First Name\n");
		DPRINTF("5. Find the Student Details by Course ID\n");
		DPRINTF("6. Find the Total number of Students\n");
		DPRINTF("7. Delete the Students Details by Roll Number\n");
		DPRINTF("8. Update Student by Roll Number\n");
		DPRINTF("9. Show all informations of the Students\n");
		DPRINTF("10. TO Exit \n");
		DPRINTF("\nChoose on of the following options :");



		scanf("%d",&option);

		switch(option)
		{
		case 1:
			DPRINTF("Add the student Details\n");
			DPRINTF("==============================\n");
			add_student_manually(&sfifo);
			break;
		case 2:
			add_student_file(&sfifo);
			break;
		case 3:
			DPRINTF("-------------------------------\n");
			find_r1(&sfifo);
			break;
		case 4:
			DPRINTF("-------------------------------\n");
			find_fn(&sfifo);
			break;
		case 5:
			DPRINTF("-------------------------------\n");
			find_c(&sfifo);
			break;
		case 6:
			DPRINTF("-------------------------------\n");
			tot_s(&sfifo);
			break;
		case 7:
			DPRINTF("-------------------------------\n");
			del_s(&sfifo);
			break;

		case 8:
			DPRINTF("-------------------------------\n");
			up_s(&sfifo);
			break;
		case 9:
			DPRINTF("-------------------------------\n");
			show_s(&sfifo);
			break;
		case 10:
			DPRINTF("-------------------------------\n");
			DPRINTF("===========Thank you===========\n");
				    exit(0);
		}

		}
	}
	else
		printf("Queue couldn't be initialized\n");
}

