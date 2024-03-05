
#include "lin.h"
struct Snode* pFirst_student = NULL;
void add_student(){
	char temp[20];
	struct Snode* pNew_student;
	struct Snode* pLast_student;
	if(pFirst_student == NULL){
		pNew_student = (struct Snode*)malloc(sizeof(struct Snode));
		pFirst_student = pNew_student;
		pNew_student->pNext_student = NULL ;
		dprintf("Enter student id: \n");
		gets(temp);
		pNew_student->data.id = atoi(temp);
		dprintf("Enter student name: \n");
		gets(pNew_student->data.name);
		dprintf("Enter student height: \n");
		gets(temp);
		pNew_student->data.height =atof(temp);
	}
	else{
		pLast_student = pFirst_student;
		while(pLast_student->pNext_student)
		{
			pLast_student = (struct Snode*)pLast_student->pNext_student;
		}
		pNew_student =(struct Snode*)malloc(sizeof(struct Snode));
		pLast_student->pNext_student = pNew_student;
		pNew_student->pNext_student = NULL;
		dprintf("Enter student id: \n");
		gets(temp);
		pNew_student->data.id = atoi(temp);
		dprintf("Enter student name: \n");
		gets(pNew_student->data.name);
		dprintf("Enter student height: \n");
		gets(temp);
		pNew_student->data.height = atof(temp);

	}

}
int Delete_student(){
 char temp_text[40];
 int selected_id;
 dprintf("\n Enter student id to be deleted: ");
 gets(temp_text);
 selected_id = atoi(temp_text);
 if(pFirst_student)
 {
	 struct Snode* pPreviousStudent = NULL;
	 struct Snode* pSelectedStudent = pFirst_student;
	 while(pSelectedStudent)
	 {
		 if(pSelectedStudent->data.id == selected_id)
		 {
			 if(pPreviousStudent)
			 {
				 pPreviousStudent->pNext_student = pSelectedStudent->pNext_student;
			 }
			 else
			 {
				 pFirst_student = pSelectedStudent->pNext_student;
			 }
			 free(pSelectedStudent);
			 return 1;
		 }
		 pPreviousStudent = pSelectedStudent;
		 pSelectedStudent = pSelectedStudent->pNext_student;
	 }
 }
 dprintf("\n cannot find student ID.")
 return 0;



}
void view_students(){
	struct Snode* pCurrent = pFirst_student;
	int count = 0;
	if(pFirst_student == NULL)
	{dprintf("\n Empty list");}
	else
	{
		while(pCurrent)
		{
			dprintf("\n record number %d",count+1);
			dprintf("\n \t ID: %d",pCurrent->data.id);
			dprintf("\n \t Name: %s",pCurrent->data.name);
			dprintf("\n \t height: %f",pCurrent->data.height);
			pCurrent = (struct Snode*)pCurrent->pNext_student;
			count++;

		}
	}
}
void Delete_all(){
	struct Snode* pCurrent = pFirst_student;
	if(pFirst_student == NULL)
	{dprintf("\n Empty list");}
	else
	{
		while(pCurrent)
		{
			struct Snode* pTemp = pCurrent;
			pCurrent = (struct Snode*)pCurrent->pNext_student;
			free(pTemp);
		}
		pFirst_student = NULL ;
	}

}
void GetNth(){
int count=0;
char temp[20];
int x;
dprintf("Enter index\n");
gets(temp);
x = atoi(temp);
struct Snode* pCount;
if(pFirst_student)
{
	pCount = pFirst_student;
	while(count != x)
	{
		pCount = pCount->pNext_student;
		count++;
	}
	dprintf("\n \t ID: %d",pCount->data.id);
	dprintf("\n \t Name: %s",pCount->data.name);
	dprintf("\n \t height: %f",pCount->data.height);
}
else
	dprintf("Empty list\n");
}
void length(){
	int count =0;
	struct Snode* pCount = pFirst_student;
	while(pCount)
	{
		count++;
		pCount = pCount->pNext_student;
	}
	dprintf("Number of nodes is %d",count);

}
void reverse_index(){
	int count =0;
	char text[20];
	int x;
	struct Snode* pCount;
	struct Snode* pBeforeCount;
	dprintf("Enter index:\n");
	gets(text);
	x = atoi(text);
	if(pFirst_student)
	{
		pCount = pFirst_student;
		pBeforeCount = pFirst_student;
		while(count != x)
		{
			pCount = pCount->pNext_student;
			count++;
		}
		while(pCount)
		{
			pCount = pCount->pNext_student;
			pBeforeCount = pBeforeCount->pNext_student;
		}
		dprintf("\n \t ID: %d",pBeforeCount->data.id);
		dprintf("\n \t Name: %s",pBeforeCount->data.name);
		dprintf("\n \t height: %f",pBeforeCount->data.height);
	}
	else
		dprintf("Empty list\n");
}
void middle(){
	struct Snode* pFast;
	struct Snode* pSlow;
	if(pFirst_student)
	{
		pFast = pFirst_student;
		pSlow = pFirst_student;
		while(1)
		{
			pFast = pFast->pNext_student;
			pFast = pFast->pNext_student;
			pSlow = pSlow->pNext_student;
			if(pFast->pNext_student == NULL)
			{
				dprintf("\n \t ID: %d",pSlow->data.id);
				dprintf("\n \t Name: %s",pSlow->data.name);
				dprintf("\n \t height: %f",pSlow->data.height);
				break;
			}
		}
	}
	else
		dprintf("Empty list\n");

}
int loop(){
		struct Snode* pFast;
		struct Snode* pSlow;
		if(pFirst_student)
		{
			pFast = pFirst_student;
			pSlow = pFirst_student;
			while(pSlow && pFast && pFast->pNext_student)
			{
				pFast = pFast->pNext_student;
				pFast = pFast->pNext_student;
				pSlow = pSlow->pNext_student;
				if(pFast == pSlow)
				{
					dprintf("There is loop\n")
					return 1;
				}
			}
		}
		else
			dprintf("Empty list\n");
	dprintf("There isnt loop\n");
	return 0;

}
