#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x,y;
	printf("Enter value of a:");
	fflush(stdin);
	fflush(stdout);
	scanf("%f",&x);
	printf("Enter value of b:");
	fflush(stdin);
	fflush(stdout);
	scanf("%f",&y);
	x=x+y;
	y=x-y;
	x=x-y;
	printf("After swapping, value of a = %.2f",x);
	printf("\nAfter swapping, value of b = %.2f",y);

	return 0;
}