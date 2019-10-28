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

enum States{start,wait, trans} state;

unsigned char button;
unsigned char button2;

unsigned char tempC;

void tick() {
	button = ~PINA & 0x01;
	button2 = ~PINA & 0x02;

	switch(state){
	    case start:
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
    }

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(1000);
    TimerOn();

    LCD_init();
    LCD_ClearScreen();

    tempC = 0x00;
    state = start;

    while(1){
		LCD_Cursor(1);
		tick();
		LCD_WriteData(tempC + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
	}
    /* Insert your solution below */
    
    return 1;
}
