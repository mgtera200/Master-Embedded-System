/*
 * main.c
 *
 * Created: 10/22/2023 3:49:55 PM
 *  Author: Dell
 */ 

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define registers_base 0x20
#define	DDRD *((volatile uint32_t *)(registers_base + 0x11))
#define	PIND *((volatile uint32_t *)(registers_base + 0x10))
#define	PORTD *((volatile uint32_t *)(registers_base + 0x12))
#define	GICR *((volatile uint32_t *)(registers_base + 0x3B))
#define	MCUCR *((volatile uint32_t *)(registers_base + 0x35))
#define	MCUCSR *((volatile uint32_t *)(registers_base + 0x34))

void pins_directions()
{
DDRD |= (1<<5);
DDRD |= (1<<6);
DDRD |= (1<<7);
PORTD |= (1<<6);
PORTD |= (1<<7);
}
void interrupt_config()
{
	GICR |= ((1<<5)|(1<<6)|(1<<7));
	//The rising edge of INT1 generates an interrupt request.
	MCUCR |= (0b11<<2);
	//Any logical change on INT0 generates an interrupt request
	MCUCR |= 0x01;
	//falling edge on INT2
	MCUCSR &= ~(1<<6);
	sei();
	
}


int main(void)
{
	pins_directions();
	interrupt_config();
    while(1)
    {
		PORTD &= ~(0b111<<5);
    }
}
ISR(INT0_vect){
	PORTD |= (1<<5);
	_delay_ms(1000);
}
ISR(INT1_vect){
	PORTD |= (1<<6);
	_delay_ms(1000);
}
ISR(INT2_vect){
	PORTD |= (1<<7);
	_delay_ms(1000);
}
