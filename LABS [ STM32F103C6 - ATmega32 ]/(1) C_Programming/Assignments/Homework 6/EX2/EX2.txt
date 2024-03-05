#include <stdio.h>

int main() {
	char arr[27];
	int i;
	char* p = arr;
	for(i=0; i<26; i++){
		*p = i+'A';
		p++;
	}
	p = arr;
	printf("The alphabets are :\n");
	for(i=0; i<26; i++){
		printf("%c\t",*p);
		p++;
	}

	return 0 ;




}
