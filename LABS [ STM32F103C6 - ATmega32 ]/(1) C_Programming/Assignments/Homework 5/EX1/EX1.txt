#include <stdio.h>
struct Sstudent
{
char name[50];
int roll;
float marks;
}x;
int main()
{
	printf("Enter student info:\n name:\n roll number:\n marks:\n");
	fflush(stdout);
	scanf("%s %d %f",&x.name,&x.roll,&x.marks);
	printf("%s %d %.2f",x.name,x.roll,x.marks);
}
