/*
 * main.c
 *
 *  Created on: Mar 22, 2023
 *      Author: MOHTERA
 */
#include <stdio.h>
int main()
{
	float a;
	printf("Enter a number:");
	fflush(stdin);
	fflush(stdout);
	scanf("%f",&a);
	if(a>0)
	{
			printf("%f is Positive",a);
	}
	else if(a<0)
	{
			printf("%f is Negative", a);
	}
	else
		printf("You entered zero");
}
