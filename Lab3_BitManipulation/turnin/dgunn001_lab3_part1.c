/*	Author: dgunn001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tmpC  = 0x00;
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    //unsigned char tmpB = 0x00; used for challenge
	/* Insert your solution below */
    
    
    while (1) {
	
        tmpA = PINA;
	tmpB = PINB;
	tmpC = 0x00;
	while(tmpA != 0x00){
	    if(tmpA & 0x01){
		tmpC++;
	    }
	    tmpA>>=1;
	}
	while(tmpB != 0x00){
	    if(tmpB & 0x01){
		tmpC++;
	    }
	    tmpB>>=1;
	}
	
	
    PORTC = tmpC;
    }
    return 1;
}
