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
	char string[50];
	int count=0;
	printf("Enter a string:\n");
	gets(string);
	for(i=0; string[i]!='\0'; i++)
	{
		++count;
	}
	printf("Length of string is %d",count);
}
