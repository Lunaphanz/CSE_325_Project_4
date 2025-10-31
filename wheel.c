/*
 * wheel.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */

#include "MKL46Z4.h"
#include "wheel.h"
#include "function.h"
void go_straight(){
	// Left motor (PTB0=AI2 high, PTB1=AI1 low)
	GPIOB->PSOR |= (1<<0);
	GPIOB->PCOR |= (1<<1);
	// Right motor (PTC1=BI1 high, PTC2=BI2 low)
	GPIOC->PSOR |= (1<<1);
	GPIOC->PCOR |= (1<<2);
	// Set PWM outputs
	setMotorSpeed(leftSpeed,rightSpeed);
}
void turn_left(){
	PRINTF("Left\n");
	// Left motor (PTB0=AI2 low, PTB1=AI1 high)
	GPIOB->PSOR |= (1<<1);
	GPIOB->PCOR |= (1<<0);
	// Right motor (PTC1=BI1 high, PTC2=BI2 low)
	GPIOC->PSOR |= (1<<1);
	GPIOC->PCOR |= (1<<2);
	// Set PWM outputs
	setMotorSpeed(leftSpeed,rightSpeed);
	delay_ms(timeTurnLeft);
	stop();
}
void turn_right(){
	PRINTF("Right\n");
	// Left motor (PTB0=AI2 high, PTB1=AI1 low)
	GPIOB->PSOR |= (1<<0);
	GPIOB->PCOR |= (1<<1);
	// Right motor (PTC1=BI1 low, PTC2=BI2 high)
	GPIOC->PSOR |= (1<<2);
	GPIOC->PCOR |= (1<<1);
	// Set PWM outputs
	setMotorSpeed(leftSpeed,rightSpeed);
	delay_ms(timeTurnRight);
	stop();
}
void turn_around(){
	// Left motor (PTB0=AI2 high, PTB1=AI1 low)
	GPIOB->PSOR |= (1<<0);
	GPIOB->PCOR |= (1<<1);
	// Right motor (PTC1=BI1 low, PTC2=BI2 high)
	GPIOC->PSOR |= (1<<2);
	GPIOC->PCOR |= (1<<1);
	// Set PWM outputs
	setMotorSpeed(leftSpeed,rightSpeed);
	delay_ms(timeTurnRight*1.5);
	stop();
}
void stop(){
	// Left motor (PTB0=AI2 low, PTB1=AI1 low)
	GPIOB->PCOR |= (1<<0);
	GPIOB->PCOR |= (1<<1);
	// Right motor (PTC1=BI1 low, PTC2=BI2 low)
	GPIOC->PCOR |= (1<<2);
	GPIOC->PCOR |= (1<<1);
	// Set PWM outputs
	setMotorSpeed(0,0);
}
void setMotorSpeed(float left, float right){
	TPM2->CONTROLS[0].CnV = left;
	TPM2->CONTROLS[1].CnV = right;
}
void delay_ms(int ms){
	int count = ms * 4800;
	while(count--){
		__asm("nop");   // no operation
	}
}



