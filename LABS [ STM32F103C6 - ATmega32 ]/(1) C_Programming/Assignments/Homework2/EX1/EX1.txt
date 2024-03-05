/*
 * main.c
 *
 *  Created on: Mar 22, 2023
 *      Author: MOHTERA
 */
#include <stdio.h>
int main()
{
int a;
printf("Enter an integer you want to check:");
fflush(stdin);
fflush(stdout);
scanf("%d", &a);
if(a%2 == 0)
	printf("%d is even", a);
else
	printf("%d is odd", a);

}

