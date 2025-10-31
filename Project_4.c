/**
 * @file    Project_4.c
 * @brief   Application entry point.
 * Name: Luan Phan
 * ASUID: 1225054597
 * Course: CSE325
 * Project 4
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "function.h"
#include "wheel.h"
#include "servo.h"
#include "ultrasonic.h"
#include "state.h"
void print(){
	PRINTF("pulse width: %d\n", pulse_width);
}
/*
 * @brief   Application entry point.
 */
int main(void) {
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    /*Configuration Setup*/
    setup_SIM_SCGC5();
    setup_SIM_SCGC6();
    setup_SOPT2(); // clock source for TPM
    setup_Wheel();
    setup_Servo();
    setup_Ultrasound();
    setup_LED();

    while(1){
    	if(SW1_press()){
    		//delay_ms(2000);
    		initial_state();
    	}
    }
    return 0 ;
}
void initial_state(){
	servo_center();
	while(!object_close){
		go_straight();
	}
	stop();
	servo_right();
	print();
	if(!object_close) {
		turn_right();
		r1();
	} else {
		l1();
	}
}
void r1(){
	servo_left();
	while (object_close){
		go_straight();
	}
	r2();
}
void r2(){
	//go pass the wall
	turn_left();
	//go pass thin wall
	turn_left();
	r3();
}
void r3(){
	servo_center();
	while(!object_close){
		go_straight();
	}
	r4();
}
void r4(){
	servo_right();
	if (object_close) {
		turn_around();
		r2();
	} else {
		turn_right();
		initial_state();
	}
}

void l1(){
	servo_left();
	if (!object_close){
		turn_left();
		l2();
	} //how about object close?
}
void l2(){
	servo_right();
	while(object_close){
		go_straight();
	}
	l3();
}
void l3(){
	//go pass the wall
	turn_right();
	//go pass thin wall
	turn_right();
	l4();
}
void l4(){
	servo_center();
	while(!object_close){
		go_straight();
	}
	l5();
}
void l5(){
	servo_left();
	if (object_close) {
		turn_around();
		l3();
	} else {
		turn_left();
		initial_state();
	}
}





