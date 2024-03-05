#include <stdio.h>
int power(int n, int pw);
int main()
{
	int i, j;
	printf("Enter base number:");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&i);
	printf("enter power number:");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&j);
	printf("%d^%d = %d",i, j, power(i,j));
	return 0;




}
int power(int i, int j)
{
	if(j!=0)
	return i*power(i,j-1);
else
	return 1;
}
