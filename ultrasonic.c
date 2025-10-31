/*
 * ultrasonic.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */
#include "MKL46Z4.h"
#include "ultrasonic.h"
int pulse_width = 0;

bool get_distant(){
	if(pulse_width < 500) return true;
	else return false;
}
void send_trigger(){
	GPIOD->PSOR = (1 << 2);  // set PTD2 GPIO high
	delay_10us();
	GPIOD->PCOR = (1 << 2);  // set PTD2 GPIO low
}
void delay_10us(){
	int count = 48;
	while(count--){
		__asm("nop");   // no operation
	}
}
