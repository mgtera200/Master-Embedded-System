/*
 * main.c
 *
 *  Created on: Apr 7, 2023
 *      Author: MOHTERA
 */

#include <stdio.h>

int main()
{
int i,j;
int r;
int c;
int matrix[100][100];
int trans[100][100];
printf("enter rows and column of matrix:");
fflush(stdout);
fflush(stdin);
scanf("%d %d",&r ,&c);
printf("enter the elements of matrix:\n");
for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		printf("\nEnter elements a%d%d:",i+1 ,j+1);
		fflush(stdout);
		fflush(stdin);
		scanf("%d",&matrix[i][j]);
	}
}
printf("Entered matrix:\n");
for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		printf("%d\t",matrix[i][j]);
		if(j==c-1)
			printf("\r\n");
	}
}

	for(i=0; i<r; i++)
	{
		for(j=0; j<c; j++)
		{
			trans[j][i]=matrix[i][j];
		}
	}
	printf("Transpose of matrix:\n");
	for(i=0; i<c; i++)
	{
		for(j=0; j<r; j++)
		{
			printf("%d\t",trans[i][j]);
			if(j==r-1)
				printf("\r\n");
		}
	}

}
