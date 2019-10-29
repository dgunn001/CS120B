/*	Author: dgunn001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0) {
	TimerISR();
	_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



enum States{start,wait, trans} state;

unsigned char button;
unsigned char button2;

unsigned char tempC;

void tick() {
	LCD_ClearScreen();
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

    TimerSet(50);
    TimerOn();

    LCD_init();
    LCD_ClearScreen();
    LCD_Cursor(1);

    tempC = 0x00;
    state = start;

    while(1){
		tick();		
		LCD_WriteData(tempC + '0');

		while(!TimerFlag){}
		TimerFlag = 0;
		
	}
    /* Insert your solution below */
    
    return 1;
}
