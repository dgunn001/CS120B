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
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF; // Configure port B's 8 pins as outputs
	PORTC = 0x00; // Initialize PORTB output to 0’s
	unsigned char cntavail = 0x00;
	unsigned char tmpA = 0x00;
    /* Insert your solution below */
    while (1) {
	cntavail = 0x00;
	tmpA = PINA; 	
	if(tmpA & 0x01){
		cntavail++;
	}
	if(tmpA & 0x02){
		cntavail++;
	}
	if(tmpA & 0x04){
		cntavail++;
	}
	if(tmpA & 0x08){
		cntavail++;
	}

	PORTC = cntavail;
    }
    return 0;
}
