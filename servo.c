/*
 * servo.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */
#include "MKL46Z4.h"
#include "servo.h"

void servo_center(){
	TPM1->CONTROLS[0].CnV = center_position;
}
void servo_right(){
	TPM1->CONTROLS[0].CnV = right_position;
}
void servo_left(){
	TPM1->CONTROLS[0].CnV = left_position;
}
