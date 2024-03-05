#include <stdio.h>
#include <string.h>
int main ()
{
	char c;
	float a;
	float b;
	printf ("Enter operator either + or - or * or divide: ");
	fflush (stdout);
	fflush(stdin);
	scanf ("%c" ,&c);
	printf("Enter two operands:");
	fflush(stdout);
	fflush(stdin);
	scanf("%f %f",&a ,&b);
	switch(c)
	{
	case '+':
				printf("%f + %f = %f",a ,b ,a+b);
				break;
	case '-':
		printf("%f - %f = %f",a ,b ,a-b);
		break;
	case '*':
		printf("%f * %f = %f",a ,b ,a*b);
		break;
	case '/':
		printf("%f / %f = %f",a ,b ,a/b);
		break;
	default:
		printf("ERROR!!Operator isn't correct");
	}
	return 0;
}


