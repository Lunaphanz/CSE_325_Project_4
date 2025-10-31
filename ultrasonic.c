/*
 * ultrasonic.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "ultrasonic.h"
int pulse_width = 0;
bool object_close = false;
bool get_distant(int distant ){
	if(distant < 350) return true;
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
