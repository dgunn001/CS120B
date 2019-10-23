nclude <avr/io.h>
#include <avr/interrupt.h>

enum States{ init, light1, light2, light3, stop,wait} state;

volatile unsigned char TimerFlag = 0; 
unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn() {

	TCCR1B = 0x0B;
	OCR1A = 125;  
	TIMSK1 = 0x02; 
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80; 
}

void TimerOff() {
	TCCR1B = 0x00; 
}


void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) { 
		TimerISR(); 
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned char button;

void cycle(){
			button = ~PINA & 0x01;
	switch (state)
	{

		case init: 
			state = light1;
		break;
		
		case light1: 
		if(button){
			state = stop;
		} else {
			state = light2;
		}
		break;
		case light2: 
		if(button){
			state = stop;
		} else {
			state = light3;
		}
		break;
		case light3: 
		if(button){
			state = stop;
		} else {
			state = light1;
		}
		break;
		case stop:
			if(button){
				state = stop;
			} else {
			state = wait;
			}
		break;
		case wait:
			if(button){
				state = light1;
			} else {
				state = wait;
			}
		break;
		default: 
		state = init;
		break;
	}
	
	switch (state)
	{
		case init: 
		PORTC = 0x00;
		break;
		case light1: 
		PORTC = 0x00;
		PORTC = 0x01;
		break;
		case light2:
		PORTC = 0x00; 
		PORTC = 0x02;
		break;
		case light3:
		PORTC = 0x00; 
		PORTC = 0x04;
		break;
		case stop:
		break;
		default:
		break;
	}
}

int main(void)
{
	state = init;
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(300);
	TimerOn();
	
	
	while (1)
	{
		cycle();
		while (!TimerFlag){}
		TimerFlag = 0;
		
	}
}
