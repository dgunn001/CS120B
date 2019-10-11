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

enum States{wait, lock,unlock,wait2} state;

unsigned char yButton;
unsigned char xButton;
unsigned char poundButton;
unsigned char lockButton;

unsigned char tempB;


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    state = lock;
    /* Insert your solution below */
    while (1) {


	switch(state){
		case wait:
			xButton = PINA & 0x01;
			yButton = PINA & 0x02;
			poundButton = PINA & 0x04;
			lockButton = PINA & 0x80;
			if(lockButton){
				state = lock;
			} else if (yButton == 0x02){
				tempB = 0x01;
				state = unlock;
			} else if (xButton == 0x01){
				state = lock;
			} else if (poundButton == 0x04){
				state = lock;
			} else { 
				state = wait;
			}
			break;
		case lock:
			xButton = PINA & 0x01;
			yButton = PINA & 0x02;
			poundButton = PINA & 0x04;
			lockButton = PINA & 0x80;			
			if(poundButton == 0x04){
				state = wait;
			} else { 
				state = lock;
			}
			break;
		case unlock: 
			xButton = PINA & 0x01;
			yButton = PINA & 0x02;
			poundButton = PINA & 0x04;
			lockButton = PINA & 0x80;			
			if(lockButton == 0x80){
				tempB = 0x00;
				state = lock;
			} else if(poundButton){
			 	state = wait2;
			} else {
				state = unlock;
			}
			break;
		case wait2:
			xButton = PINA & 0x01;
			yButton = PINA & 0x02;
			poundButton = PINA & 0x04;
			lockButton = PINA & 0x80;
			if(lockButton){
				state = lock;
			} else if (yButton == 0x02){
				tempB = 0x00;
				state = lock;
			} else if (xButton == 0x01){
				state = unlock;
			} else if (poundButton == 0x04){
				state = unlock;
			} else { 
				state = wait2;
			}
			break;
	}
	PORTB = tempB;
    }
    return 1;
}
