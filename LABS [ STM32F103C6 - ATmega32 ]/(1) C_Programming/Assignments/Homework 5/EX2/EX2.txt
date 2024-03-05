#include <stdio.h>
#include <math.h>
struct Sdistance
{
float inch;
int feet;
}x,y,z;
int main()
{
	printf("Enter info for first distance\n");
	printf("Enter feet:");
	fflush(stdout);
	scanf("%d",&x.feet);
	printf("\nEnter inch:");
	fflush(stdout);
	scanf("%f",&x.inch);
	printf("\nEnter information for second distance");
	printf("\nEnter feet:");
	fflush(stdout);
	scanf("%d",&y.feet);
	printf("\nEnter inch:");
	fflush(stdout);
	scanf("%f",&y.inch);
	z.feet=x.feet+y.feet;
	z.inch=x.inch+y.inch;
	if(z.inch>12){
		z.feet+=(int)z.inch/12;
	    z.inch-=12*(int)z.inch/12;
	}
	printf("Sum of distances: %d\'-%.1f\"",z.feet,z.inch);
}
