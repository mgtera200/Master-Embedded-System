#include "uart.h"
#include <stdio.h>
unsigned char string[100]= "learn-in-depth:<TERA>";
unsigned char const string_2[100]= "to create a rodata section";
int main(){
send_string(string);			
}