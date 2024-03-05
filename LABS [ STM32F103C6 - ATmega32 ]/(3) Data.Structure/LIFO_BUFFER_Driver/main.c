//ENG.TERA
//ENG.TERA
#include "stdio.h"
#include "lifo.h"
#include "stdlib.h"
unsigned int buff1[5];
int main() {
	unsigned int i,temp;
	LIFO_BUF_t uart_lifo;
	if(LIFO_BUF_init(&uart_lifo,buff1,5)== LIFO_NO_ERROR){

		for(i=0; i<7; i++)
		{

			if(Enqueue(&uart_lifo,i)== LIFO_NO_ERROR){
				printf("Enqueue done : %d \n",i);
			}
			else if(Enqueue(&uart_lifo,i)== LIFO_FULL)
			{
				printf("BUFF IS FULL! \n");
			}
		}
		printf("---------------------\n");
		for(i=0; i<7; i++)
		{

			if(Dequeue(&uart_lifo,&temp)== LIFO_NO_ERROR){
				printf("Dequeue done : %d \n",temp);
			}
			else if(Dequeue(&uart_lifo,&temp)== LIFO_EMPTY)
			{
				printf("BUFF IS EMPTY! \n");
			}
		}
		return 0;

	}
	else
		printf("LIFO IS NULL!");







}

