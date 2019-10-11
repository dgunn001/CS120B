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

enum States{start,wait} state;

unsigned char button;
unsigned char button2;

unsigned char tempB;


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    state = start;
    /* Insert your solution below */
    while (1) {
	button = ~PINA & 0x01;
	button2 = ~PINA & 0x02;

	switch(state){
	    case start: 
		if(button && button2){
			if(tempB == 0x01){
				tempB = 0x02;
			} else {
				tempB = 0x01;
			}
			state = wait;
		} else {
			state = start;
		}
		break;
	    case wait:
		if(!button && !button2){
			state = start;
		} else {
			state = wait;
		}
		break;
	}
	PORTB = tempB;
    }
    return 1;
}
