/*
 * main.c
 *
 *  Created on: Apr 7, 2023
 *      Author: MOHTERA
 */

#include <stdio.h>

int main()
{
	int i;
int n;
int matrix[50];
int search;
printf("enter number of elements:");
fflush(stdout);
fflush(stdin);
scanf("%d",&n);
printf("Enter the elements:");
fflush(stdout);
fflush(stdin);
for(i=0; i<n; i++)
{
	scanf("%d",&matrix[i]);
}
printf("Enter the elements to be searched:");
fflush(stdout);
fflush(stdin);
scanf("%d",&search);
for(i=0; i<n; i++)
{
	if(matrix[i]==search)
		printf("Number found at location %d",i+1);
}











}
