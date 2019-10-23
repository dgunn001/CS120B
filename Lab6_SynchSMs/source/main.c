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
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x08;
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

unsigned char tmpC = 0x00;
enum States{init, light1, light2 , light3}state;

void cycle3(){
	switch(state){
	case init:
	state = light1;
	break;
	case light1:
	state = light2;
	break;
	case light2:
	state = light3;
	break;
	case light3:
	state = light1;
	break;
	}
	switch(state){
	case light1:
	tmpC = 0x01;
	break;
	case light2:
	tmpC = 0x02;
	break;
	case light3:
	tmpC = 0x04;
	break;
	}
}
	
	


	


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
	state = init;
	
    while (1) {
	lightTick();
	while(!TimerFlag);
	TimerFlag = 0;
	PORTC = tmpC;
    }
    return 0;
}
