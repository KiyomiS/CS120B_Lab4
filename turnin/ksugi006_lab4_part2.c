/*	Author: ksugi006
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, check, dec, inc, decP, incP} state;

void Tick(){
	switch(state){//transitions
		case Start:
			state = check;
			PORTC = 0x07;
			break;
		case check:
			if ((PINA & 0x01) == 0x01){
				state = inc;
			}
			else if ((PINA & 0x02) == 0x02){
				state = dec;
			}
			break;
		case inc:
			state = incP;
			break;
		case dec:
			state = decP;
			break;
		case incP:
			if((PINA & 0x01) == 0x01){
				state = incP;
			}
			else {
				state = check;
			}
			break;
		case decP:
			if((PINA & 0x02) == 0x02) {
				state = decP;
			}
			else {
				state = check;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state){//state actions
		case Start:
			break;
		case check:
			if((PINA & 0x03) == 0x03){
				PORTC = 0x00;
			}
			break;
		case inc:
			if(PORTC < 0x09) {
				PORTC= PORTC + 1;
			}
			break;
		case dec:
			if(PORTC > 0x00) {
				PORTC = PORTC - 1;
			}
			break;
		case incP:
			if((PINA& 0x03) == 0x03) {
				PORTC = 0x00;
			}
			break;
		case decP:
			if((PINA & 0x03) == 0x03) {
				PORTC = 0x00;
			}
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	state = Start;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
