/*
 * main.c
 *
 *  Created on: Mar 22, 2023
 *      Author: MOHTERA
 */
#include <stdio.h>
int main()
{
float a, b;
float multi;
printf("Enter two numbers:");
fflush(stdin);
fflush(stdout);
scanf("%f %f", &a, &b);
multi=a*b;
printf("Product: %f", multi);
}

