

rtner(s) Name: 
 *	Lab Section:
 *	 *	Assignment: Lab #  Exercise #
 *	  *	Exercise Description: [optional - include for your own benefit]
 *	   *
 *	    *	I acknowledge all content contained herein, excluding template or example
 *	     *	code, is my own original work.
 *	      */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,wait, trans} state;

unsigned char button;
unsigned char button2;

unsigned char tempC;


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    tempC = 0x07;
    state = start;
    /* Insert your solution below */
    while (1) {
	button = PINA & 0x01;
	button2 = PINA & 0x02;

	switch(state){
	    case start:
		tempC = 0x07; 
		if(button && !button2){
			if(tempC < 9){
			   tempC++;
			   state = wait;
			} else {
			   state = wait;
			}
		} else if (!button && button2) {
			if(tempC > 0){
			   tempC--;
			   state = wait;
			} else {
			   state = wait;
			}
		} else if (button && button2){
			tempC = 0;
			state = wait;
		} else {
			state = trans;
		}
		break;
	    case trans: 
		if(button && !button2){
			if(tempC < 9){
			   tempC++;
			   state = wait;
			} else {
			   state = wait;
			}
		} else if (!button && button2) {
			if(tempC > 0){
			   tempC--;
			   state = wait;
			} else {
			   state = wait;
			}
		} else if (button && button2){
			tempC = 0;
			state = wait;
		} else {
			state = trans;
		}
		break;
	    case wait:
		if(!button && !button2){
			state = trans;
		} else if(button && button2){
			tempC = 0;
			state = wait;
		} else {
			state = wait;
		}
		break;
	}
	PORTC = tempC;
    }
    return 1;
}

