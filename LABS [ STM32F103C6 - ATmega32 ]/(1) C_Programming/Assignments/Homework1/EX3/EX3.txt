/*
 * main.c
 *
 *  Created on: Mar 22, 2023
 *      Author: MOHTERA
 */
#include <stdio.h>
int main()
{
int a, b;
int sum;
printf("Enter two integers:");
fflush(stdin);
fflush(stdout);
scanf("%d %d", &a, &b);
sum=a+b;
printf("Sum: %d", sum);
}

