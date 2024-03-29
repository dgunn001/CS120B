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

void set_PWM(double frequency) {
	static double current_frequency; 
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States{off, turnOff, on, compOn, up, waitUp, down, waitDown}state;


unsigned char buttonPress = 0x00;

const double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i = 0x00;

void button_Tick(){
	buttonPress = ~PINA & 0x07;
	switch(state){ // Transitions
		case off:
			if(buttonPress == 1)
				state = on;
			else
				state = off;
			break;
		case turnOff:
			if(!(buttonPress == 1))
				state = off;
			else
				state = turnOff;
			break;
		case on:
			if(buttonPress == 1)
				state = on;
			else
				state = compOn;
			break;
		case compOn:
			if(buttonPress == 2){
				if(i < 7)
					i++;
				state = up;
			}
			else if(buttonPress == 4){
				if(i > 0)
					i--;
				state = down;
			}
			else if(buttonPress == 1)
				state = turnOff;
			else
				state = compOn;
			break;
		case up:
			state = waitUp;
			break;
		case waitUp:
			if(buttonPress == 2)
				state = waitUp;
			else
				state = compOn;
			break;
		case down:
			state = waitDown;
			break;
		case waitDown:
			if(buttonPress == 4)
				state = waitDown;
			else
				state = compOn;
			break;
	}
	switch(state){ // State actions
		case off:
			PWM_off();
			break;
		case turnOff:
			break;
		case on:
			PWM_on();
			break;
		case compOn:
			break;
		case up:
			set_PWM(notes[i]);
			break;
		case waitUp:
			break;
		case down:
			set_PWM(notes[i]);
			break;
		case waitDown:
			break;

	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
	DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00
	PWM_on();
	state = off;
	while(1){
		button_Tick();
	}
}
