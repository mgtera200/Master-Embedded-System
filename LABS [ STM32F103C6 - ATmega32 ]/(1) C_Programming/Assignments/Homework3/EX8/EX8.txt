/*
 * main.c
 *
 *  Created on: Apr 7, 2023
 *      Author: MOHTERA
 */

#include <stdio.h>
#include <string.h>
int main()
{
	char string[50];
	char reverse[50];
	int i;
	int j=0;
	printf("\nEnter the string:");
	fflush(stdout);
	fflush(stdin);
	gets(string);
	for(i=strlen(string)-1; i>=0; i--)
	{
		reverse[j]=string[i];
		j++;
	}
	reverse[strlen(string)]='\0';
	printf("\nReverse string is :%s",reverse);


}
