/*
 ENG-TERA
 */
#include "studentbase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
queue_status Fifo_init(fifo *pFifo,sinfo *buff){

	if(pFifo != NULL){
		pFifo->base = buff;
		pFifo->head = buff;
		pFifo->count = 0;
		pFifo->tail = buff;
		pFifo->length = 50;
		return queue_no_error;
	}
	return queue_NULL;

}
void add_student_file(fifo *pFifo){
	FILE* txt_file = fopen("Student.txt","r");
	char* taken;
	char delimiter[50];
	int  count = 0, flag = 0 ,Record = 0;


	while(fgets(delimiter,sizeof delimiter,txt_file) != NULL)
	{
		Record++;
		taken = strtok(delimiter," ");
		count =0 ;

		while(taken != NULL)
		{
			count++;

			if(count == 1)
			{
				if(check_roll(pFifo, atoi(taken)) == 1)
				{
					DPRINTF("[ERROR] Roll Number %d is already Taken\n",atoi(taken));
					flag++;
					break;
				}
				else
				{
					pFifo->head->roll = atoi(taken);
					DPRINTF("[INFO] Roll Number %d is saved successfully\n",atoi(taken));
				}
			}

			else if(count == 2)
			{
				strcpy(pFifo->head->fname , taken);
			}
			else if(count == 3)
			{
				strcpy(pFifo->head->lname , taken);
			}
			else if(count == 4)
			{
				pFifo->head->GPA = atof(taken);
			}
			else if(count == 5)
			{
				pFifo->head->cid[0] = atoi(taken);
			}
			else if(count == 6)
			{
				pFifo->head->cid[1] = atoi(taken);
			}
			else if(count == 7)
			{
				pFifo->head->cid[2] = atoi(taken);
			}
			else if(count == 8)
			{
				pFifo->head->cid[3] = atoi(taken);
			}
			else if(count == 9)
			{
				pFifo->head->cid[4] = atoi(taken);
			}

			taken = strtok(NULL," \n");
		}

		if(check_roll(pFifo, atoi(taken)) == 1)
			continue;

		pFifo->count++;
		pFifo->head++;
	}
	fclose(txt_file);

	DPRINTF("\n*******************************************\n");
	DPRINTF("\n[INFO] students Details is added successfully");
	DPRINTF("\n*******************************************\n");

	tot_s(pFifo);
}

void enqueue(fifo *pFifo,sinfo *new_student){
	if(pFifo->count == pFifo->length){
		DPRINTF("Queue is Full\n");
	}
	else{
		int i,j;
		for(i=0; i<50; i++){
			pFifo->head->fname[i] = new_student->fname[i];
			pFifo->head->lname[i] = new_student->lname[i];
		}
		pFifo->head->roll = new_student->roll;
		pFifo->head->GPA = new_student->GPA;
		for(j=0; j<5; j++){
			pFifo->head->cid[j] = new_student->cid[j];
		}
		//Check circular queue
		if(pFifo->head == ((pFifo->base)+sizeof(sinfo)*50))
			pFifo->head = pFifo->base;
		else
			pFifo->head++;
		pFifo->count ++;
	}
}

void dequeue(fifo *pFifo,sinfo* temp)
{
	if(pFifo->count == 0){
		DPRINTF("queue is empty\n");
	}
	else{
		int i,j;
		for(i=0; i<50; i++){
			temp->fname[i]= pFifo->tail->fname[i];
			temp->lname[i]= pFifo->tail->lname[i];
		}
		for(j=0; j<5; j++){
			temp->cid[j]= pFifo->tail->cid[j];
		}
		temp->GPA= pFifo->tail->GPA;
		temp->roll= pFifo->tail->roll;
		//Check circular queue
		if(pFifo->tail == ((pFifo->base)+sizeof(sinfo)*50))
			pFifo->tail = pFifo->base;
		else
			pFifo->tail++;
		pFifo->count --;
		DPRINTF("Dequeue is Done !\n");
	}
}


int check_roll(fifo *pFifo, int roll){
	int i;
	sinfo *ptr=pFifo->tail;
	if(pFifo->count == 0)
		return 0;
	for(i=0; i<pFifo->count; i++){
		if(ptr->roll == roll)
			return 1;
		else if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
			ptr = pFifo->base;
		else
			ptr++;
	}
	return 0;
}
void tot_s(fifo *pFifo){
	DPRINTF("------------------------------\n");
	DPRINTF("[INFO] The total number of students is %d\n",pFifo->count);
	DPRINTF("[INFO] You can add up to %d students\n",pFifo->length);
	DPRINTF("[INFO] You can add %d more students\n",((pFifo->length)-(pFifo->count)));
}

void add_student_manually(fifo *pFifo){
	if(pFifo->count != pFifo->length)
	{
		int i;
		sinfo new_student;
		DPRINTF("Enter the Roll number:\n");
		scanf("%d",&new_student.roll);
		if(check_roll(pFifo,new_student.roll)==0){
			DPRINTF("Enter the first name of student:\n");
			scanf("%s",(char*)&new_student.fname);
			DPRINTF("Enter the last name of student\n");
			scanf("%s",(char*)&new_student.lname);
			DPRINTF("Enter the GPA you obtained:\n");
			scanf("%f",&new_student.GPA);
			DPRINTF("Enter the course ID of each course\n");
			for(i=0; i<5; i++)
			{
				DPRINTF("Course %d id:",i+1);
				scanf("%d",&new_student.cid[i]);
			}
			enqueue(pFifo,&new_student);
			DPRINTF("[INFO] Student Details is added successfully\n");
			tot_s(pFifo);
		}
		else
			DPRINTF("[ERROR] Roll number is already taken\n");
	}
	else
		DPRINTF("Queue is Full");

}
void find_r1(fifo *pFifo){
	int roll;
	int i,j;
	sinfo *ptr= pFifo->tail;

	if(pFifo->count == 0){
		DPRINTF("Queue is empty\n");
	}
	else{

		DPRINTF("Enter the Roll number of the student:\n");
		scanf("%d",&roll);

		if(check_roll(pFifo,roll)==0)
			DPRINTF("[ERROR] Roll number %d not found\n",roll);

		for(i=0; i<pFifo->count; i++){

			if(ptr->roll == roll){

				DPRINTF("The student details are\n");
				DPRINTF("The first name is %s\n",ptr->fname);
				DPRINTF("The last name is %s\n",ptr->lname);
				DPRINTF("The GPA is %f\n",ptr->GPA);

				for(j=0; j<5; j++)
					DPRINTF("The courses ID are %d\n",ptr->cid[j]);

			}
			if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
				ptr = pFifo->base;

			else
				ptr++;
		}
	}
}
void find_fn(fifo *pFifo){
	if(pFifo->count == 0){
		DPRINTF("Queue is empty\n");
	}
	else{

		int i,j;
		int flag=0;
		char student[50];
		sinfo *ptr= pFifo->tail;

		DPRINTF("Enter the first name of the student:\n");
		scanf("%s",student);
		for(i=0; i<pFifo->count; i++){

			if(stricmp(ptr->fname,student)==0)
			{
				flag=1;
				DPRINTF("The student details are\n");
				DPRINTF("The first name is %s\n",ptr->fname);
				DPRINTF("The last name is %s\n",ptr->lname);
				DPRINTF("The roll number is %d\n",ptr->roll);
				DPRINTF("The GPA is %f\n",ptr->GPA);

				for(j=0; j<5; j++)
					DPRINTF("The courses ID are %d\n",ptr->cid[j]);

			}
			if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
				ptr = pFifo->base;

			else
				ptr++;
		}

		if(flag==0)
			DPRINTF("[ERROR] First name %s not found\n",student);
	}
}

void find_c(fifo *pFifo){
	if(pFifo->count == 0)
	{
		DPRINTF("Queue is empty\n");
	}
	else
	{
		int i,j,k;
		int num;
		int flag=0;
		sinfo *ptr= pFifo->tail;

		DPRINTF("Enter the course ID:\n");
		scanf("%d",&num);
		for(i=0; i<pFifo->count; i++){
			for(j=0; j<5; j++){
				if(ptr->cid[j]==num)
				{

					DPRINTF("The student details are\n");
					DPRINTF("The first name is %s\n",ptr->fname);
					DPRINTF("The last name is %s\n",ptr->lname);
					DPRINTF("The roll number is %d\n",ptr->roll);
					DPRINTF("The GPA is %f\n",ptr->GPA);
					for(k=0; k<5; k++)
						DPRINTF("The courses ID are %d\n",ptr->cid[k]);
					flag=1;
				}
			}
			if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
				ptr = pFifo->base;

			else
				ptr++;
		}
		if(flag==0)
			DPRINTF("[ERROR] Course ID %d not found\n",num);
	}

}
void del_s(fifo *pFifo){
	int flag=0;

	if(pFifo->count == 0){
		DPRINTF("Queue is empty\n");
		flag=1;
	}
	if(flag==0){
		int roll,i;
		sinfo *ptr= pFifo->tail;

		DPRINTF("Enter the roll number which you want to delete:\n");
		scanf("%d",&roll);

		if(check_roll(pFifo,roll)==1){
			for(i=0; i<pFifo->count; i++){
				if(ptr->roll == roll){
					*ptr = *pFifo->tail;
					if(pFifo->tail == ((pFifo->base)+sizeof(sinfo)*50))
						pFifo->tail = pFifo->base;
					else
						pFifo->tail++;
					pFifo->count --;
					DPRINTF("[INFO] The roll number is removed successfully\n");
					tot_s(pFifo);
				}
				if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
								ptr = pFifo->base;

							else
								ptr++;
			}
		}
		else
			DPRINTF("[ERROR] The roll number %d not found\n",roll);
	}
}
void up_s(fifo *pFifo){
	int flag=0;

	if(pFifo->count ==0){
		DPRINTF("Queue is empty\n");
		flag=1;
	}
	if(flag==0){

		int i,cases,roll;
		sinfo *ptr = pFifo->tail;

		DPRINTF("Enter the roll number which you want to update:\n");
		scanf("%d",&roll);

		if(check_roll(pFifo,roll)==1){

			for(i=0; i<pFifo->count; i++){

				if(ptr->roll == roll){

					DPRINTF(" 1. Student first name :\n 2. Student last name :\n 3. Student ID number :\n 4. Student GPA :\n 5. courses\n");
					scanf("%d",&cases);

					switch(cases)
					{
					case 1:
						DPRINTF("Enter Student first name :\n");
						scanf("%s",(ptr->fname));
						break;
					case 2:
						DPRINTF("Enter Student last name :\n");
						scanf("%s",(ptr->lname));
						break;
					case 3:
						DPRINTF("Enter Student Roll Number  :\n");
						scanf("%d",&(ptr->roll));
						break;
					case 4:
						DPRINTF("Enter Student GPA\n");
						scanf("%f",&(ptr->GPA));
						break;
					case 5:
						DPRINTF("Enter The Courses\n");
						for(i=0;i<5;i++)
						{
							scanf("%d",&(ptr->cid[i]));
						}
						break;
					}
				}

				if(ptr == ((pFifo->base)+sizeof(sinfo)*50))
					ptr = pFifo->base;

				else
					ptr++;
			}
		}
		else
			DPRINTF("[ERROR] The roll number %d not found\n",roll);
	}

}
void show_s(fifo *pFifo){
	if(pFifo->count ==0)
		DPRINTF("Queue is Empty\n");

	int i,j;
	sinfo *ptr=pFifo->tail;

	for(i=0;i<pFifo->count;i++,ptr++)
	{
		DPRINTF("The Students Details are\n");
		DPRINTF("Student first name : %s\n",ptr->fname);
		DPRINTF("Student last name : %s\n",ptr->lname);
		DPRINTF("Student Roll Number : %d\n",ptr->roll);
		DPRINTF("Student GPA : %.2f\n",ptr->GPA);
		DPRINTF("the courses id's are \n");
		for(j=0;j<5;j++)
		{
			DPRINTF("course ID : %d \n",ptr->cid[j]);
		}
	}
	tot_s(pFifo);
}




