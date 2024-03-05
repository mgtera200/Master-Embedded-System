// ENG.TERA
#include "stdio.h"
#include "fifo.h"
int main(){
	int i;
	unsigned char temp =0;
	unsigned char buf[5];
	FIFO_BUF_t FIFO;
	if(FIFO_BUF_init(&FIFO,buf,5)==FIFO_NO_ERROR){
		for(i=0; i<7; i++)
		{

			if(Enqueue(&FIFO,i)== FIFO_NO_ERROR){
				printf("Enqueue done : %d \n",i);
			}
			else if(Enqueue(&FIFO,i)== FIFO_FULL)
			{
				printf("BUFF IS FULL! \n");
			}
		}
		printf("---------------------\n");
		for(i=0; i<2; i++)
		{

			if(Dequeue(&FIFO,&temp)== FIFO_NO_ERROR){
				printf("Dequeue done : %d \n",temp);
			}
			else if(Dequeue(&FIFO,&temp)== FIFO_EMPTY)
			{
				printf("BUFF IS EMPTY! \n");
			}
		}
		printf("---------------------\n");
		for(i=0; i<4; i++)
		{

			if(Enqueue(&FIFO,i)== FIFO_NO_ERROR){
				printf("Enqueue done : %d \n",i);
			}
			else if(Enqueue(&FIFO,i)== FIFO_FULL)
			{
				printf("BUFF IS FULL! \n");
			}
		}
		printf("---------------------\n");
		for(i=0; i<2; i++)
		{

			if(Dequeue(&FIFO,&temp)== FIFO_NO_ERROR){
				printf("Dequeue done : %d \n",temp);
			}
			else if(Dequeue(&FIFO,&temp)== FIFO_EMPTY)
			{
				printf("BUFF IS EMPTY! \n");
			}
		}
		printf("---------------------\n");
		for(i=2; i<4; i++)
		{

			if(Enqueue(&FIFO,i)== FIFO_NO_ERROR){
				printf("Enqueue done : %d \n",i);
			}
			else if(Enqueue(&FIFO,i)== FIFO_FULL)
			{
				printf("BUFF IS FULL! \n");
			}
		}


	}
	else
		printf("LIFO IS NULL!");


}






