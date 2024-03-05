#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int y;
	char x;
	for(y=0;y<2;y++){
		fflush(stdin);
		fflush(stdout);
		printf("Enter an intger you want to check:");
		fflush(stdin);
		fflush(stdout);
		scanf("%c",&x);
		if(x=='a'|| x=='e' || x=='i' || x=='o' || x=='u')
			printf("%c is vowel.\n",x);
		else
			printf("%c is constant.\n",x);
	}


	return 0;
}