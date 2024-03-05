#include <stdio.h>
#define PI 3.1415
#define area(r) (PI*(r)*(r))
int main(){
	int radius;
	float area;
	printf("Enter the radius:");
	fflush(stdout);
	scanf("%d",&radius);
	area=area(radius);
	printf("Area=%.2f",area);
	return 0;
}
