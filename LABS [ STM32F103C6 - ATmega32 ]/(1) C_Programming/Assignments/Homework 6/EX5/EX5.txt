#include <stdio.h>
#include <string.h>

int main() {

	struct employees {
		char *name;
		int id;

	};
	struct employees str1 = {"khaled",100};
	struct employees str2 = {"Alex",1002};
	struct employees str3 = {"noha",512};
	struct employees*arr[]={&str1,&str2,&str3};
	struct employees*(*ptr4)[3]=&arr;
	printf("Employee name : %s\n",(**(*ptr4+1)).name);
	printf("Employee id is %d",(*(*ptr4+1))->id);
	return 0;





}
