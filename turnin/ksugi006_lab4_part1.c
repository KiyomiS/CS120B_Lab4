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

enum States{Start, OFFR, ONP, ONR, OFFP} state;

void Tick(){
	switch(state){//transitions
		case Start:
			state = OFFR;
			break;
		case OFFR:
			if((PINA & 0x01) == 0x01){
				state = ONP;
			}
			break;
		case ONP:
			if((PINA & 0x01) != 0x01){
				state = ONR;
			}
			break;
		case ONR:
			if((PINA & 0x01) == 0x01){
				state = OFFP;
			}
			break;
		case OFFP:
			if((PINA & 0x01) != 0x01){
				state = OFFR;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state){//state actions
		case Start:
			break;
		case OFFR:
			PORTB = 0x01;
			break;
		case ONP:
			PORTB = 0x02;
			break;
		case ONR:
			break;
		case OFFP:
			PORTB = 0x01;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	state = Start;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
