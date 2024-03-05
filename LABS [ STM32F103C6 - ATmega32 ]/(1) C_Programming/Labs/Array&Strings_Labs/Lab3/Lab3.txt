#include <stdio.h>
#include <string.h>

int main (){
	float matrix[3][3];
	float transpose[3][3];
	int r;
	int c;
	for(r=0; r<3; r++)
	{
		for(c=0; c<3; c++)
		{
			printf("\nEnter the item(%d,%d):",r ,c);
			fflush(stdout); fflush(stdin);
			scanf("\n%f", &matrix[r][c]);
		}
	}
	printf("The matrix is:\n");
	for (r=0; r<3; r++)
	{
		for(c=0; c<3; c++)
		{
			printf("%f\t ", matrix[r][c]);
		}
		printf("\r\n");
	}
	for(r=0; r<3; r++)
	{
		for(c=0; c<3; c++)
		{
			transpose[r][c]= matrix[c][r];
		}
	}

	printf("The transpose is:\n");
	for(r=0; r<3; r++)
	{
		for(c=0; c<3; c++)
		{
			printf("%f\t", transpose[r][c]);
		}
		printf("\r\n");
	}






}
