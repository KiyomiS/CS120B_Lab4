/*	Author: ksugi006
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, loop, next} state;
unsigned char cnt;
unsigned char arr[4] = { 0x04, 0x00, 0x01, 0x00}; // # X Y X
void Tick() {
	switch(state) {
		case Start:
			state = loop;
			break;
		case loop:
			if (PINA == 0x80) {
				state = Start;
			}
			if( cnt == 4) {
				state = next;
			}
			break;
		case next:
			state = Start;
			break;
		default:
			state = Start;
			break;

	}
	switch(state) {
		case Start:
			break;
		case loop:
			if(PINA == 0x80) {
				PORTB = 0x00;
				cnt = 0;
			}
			if(PINA == arr[cnt]){
				cnt = cnt + 1;
			}
			else {
				cnt = 0;
			}
			break;
		case next:
			if(PINA == 0x80) {
				PORTB = 0x00;
			}
			else if (PORTB == 0x00) {
				PORTB = 0x01; //switching states from lock to unlock now
			}
			else if (PORTB == 0x01) {
				PORTB = 0x00; //switching from unlock to lock --> probably should rename the lock state to change lock..
			}
			break;
		default:
			PORTB = 0x00;
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
