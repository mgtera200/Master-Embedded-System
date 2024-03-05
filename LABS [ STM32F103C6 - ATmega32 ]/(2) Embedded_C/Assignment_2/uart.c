#include "uart.h"
#define UARTDR *((volatile unsigned int *)((unsigned int*)0x101f1000))
void send_string(unsigned char *P_tx_string)
{
while(*P_tx_string != '\0')
{
UARTDR = (unsigned int)(*P_tx_string);
P_tx_string++;
}
}