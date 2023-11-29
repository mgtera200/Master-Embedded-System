//ENG.TERA

#include <stdint.h>
typedef volatile unsigned int vuint32_t;

#define SYSCTL_RCG2_R     (*((volatile unsigned long*)0x400FE108))
#define GPIO_PORTF_DIR_R  (*((volatile unsigned long*)0x40025400))
#define GPIO_PORTF_DEN_R  (*((volatile unsigned long*)0x4002551C))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long*)0x400253FC))

int main(void)
{
	volatile unsigned long delay_count;
	SYSCTL_RCG2_R =0x20;
	// Delay to make sure GPIOF is up and running
	for (delay_count = 0; delay_count < 200000; delay_count++);
	GPIO_PORTF_DIR_R |= 1<<3 ; //Dir is output for Pin 3 Port F
	GPIO_PORTF_DEN_R |= 1<<3 ;
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3 ;
		for (delay_count = 0; delay_count < 200000; delay_count++);
		GPIO_PORTF_DATA_R &= ~(1<<3);
		for (delay_count = 0; delay_count < 200000; delay_count++);
	}
	return 0;
}

