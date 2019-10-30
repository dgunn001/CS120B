/*	Author: dgunn001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1<< ADSC) | (1<<ADATE);
}

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();
	while(1){
		unsigned short x = ADC;
		unsigned char bPort = (char)x;
		PORTB = aPort;
		unsigned char dPort = (char)(x >> 8);
		PORTD = dPort;
	}
}
