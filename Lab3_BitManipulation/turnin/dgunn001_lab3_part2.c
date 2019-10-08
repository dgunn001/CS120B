
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


   //unsigned char tmpB = 0x00; used for challenge


	/* Insert your solution below */
   while (1) {
	tmpA = PINA & 0x0F;
	switch(tmpA){
		case 1:
		case 2:
		   tmpC = 0x20;
		   tmpC = tmpC | 0x40;
		break;
		case 3:
		case 4:
		   tmpC = 0x30;
		   tmpC = tmpC | 0x40;
		break;
		case 5:
		case 6:
		   tmpC = 0x38;
		break;
		case 7:
		case 8:
		case 9:
		   tmpC = 0x3C;
		break;
		case 10:
		case 11:
		case 12:
		   tmpC = 0x3E;
		break;
		case 13:
		case 14:
		case 15:
		   tmpC = 0x3F;
		break;


	}


   PORTC = tmpC;


   }


   return 1;


}


