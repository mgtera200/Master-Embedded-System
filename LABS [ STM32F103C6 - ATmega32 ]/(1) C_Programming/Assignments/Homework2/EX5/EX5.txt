/*
 * main.c
 *
 *  Created on: Mar 22, 2023
 *      Author: MOHTERA
 */
#include <stdio.h>
int main()
{
	char c;
		printf ("Enter a character : ");
		fflush (stdout );
		scanf ("%c", &c);
		if ((c >='a' && c <='z') || (c >='A' && c <='Z'))
			printf ("%c is a alphabet",c);
		else
			printf ("%c is not alphabet",c);
}
