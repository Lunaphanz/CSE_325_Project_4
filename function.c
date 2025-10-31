/*
 * function.c
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
#include "function.h"
#include "wheel.h"
#include "ultrasonic.h"
#include "servo.h"
//configuration
void setup_SIM_SCGC5(){
	//enable clock gating Port A,B,C,D
	//                        9,10,11,12
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1) |
				  SIM_SCGC5_PORTB(1) |
				  SIM_SCGC5_PORTC(1) |
				  SIM_SCGC5_PORTD(1);
}
void setup_SIM_SCGC6(){
	//enable clock gating TPM0, TPM1, TPM2, PIT
	// 					   24	 25    26   23
	SIM->SCGC6 |= SIM_SCGC6_TPM0(1) |
				  SIM_SCGC6_TPM1(1) |
				  SIM_SCGC6_TPM2(1) |
				  SIM_SCGC6_PIT(1);
}
void setup_SOPT2(){
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(2); //OSCERCLK bit 24-25
}
void setup_Wheel(){
	setup_PortB();
	setup_PortC(); //wheel motor and switch
	setup_TPM2();
}
void setup_Servo(){
	setup_PTA12();
	setup_TPM1();
}
void setup_Ultrasound(){
	setup_PTD2();
	setup_PTA13();
	setup_PIT();
}
void setup_PTD2(){
	PORTD->PCR[2] &= ~(0x700);
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1<<2);
}
void setup_PTA13(){
	//PTA13 to GPIO, interrupt on either edge,  input
	PORTA->PCR[13] &= ~(0xF700);
	PORTA->PCR[13] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(11);
	GPIOA->PDDR &= ~(1<<13); // Clear Data direction (input)
	NVIC_EnableIRQ(30);
}
void setup_PIT(){
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = 2100000; // 100 ms
	PIT->CHANNEL[0].TCTRL = 0x3; // enable Timer 0 interrupts and start timer.
	//-----
	PIT->CHANNEL[1].LDVAL = 21; // 1 us
	//-----

	NVIC_EnableIRQ(22);
}
void PIT_IRQHandler(){
	if(PIT->CHANNEL[0].TFLG){ // Timer 0 Triggered
		send_trigger();
		object_close = get_distant();
		PIT->CHANNEL[0].TFLG = 1; // Reset
	}
	if(PIT->CHANNEL[1].TFLG){ // Timer 1 Triggered
		pulse_width++;
		PIT->CHANNEL[1].TFLG = 1; // Reset
	}
}

void PORTA_IRQHandler(){
	PORTA->ISFR |= (1 << 13); // clear flag
	if(GPIOA->PDIR & (1<<13)){
		PIT->CHANNEL[1].TCTRL = 0x3; // enable Timer 1 interrupts and start timer.
	} else {
		PRINTF("pulse width: %d\n", pulse_width);
		PIT->CHANNEL[1].TCTRL = 0x0; // disable Timer 1.
		pulse_width = 0;
	}
}
void setup_TPM1(){
	//Set up TPM1, PS = 4, Clock Mod increment
	PRINTF("TPM1 configured\n");
	TPM1->SC |= TPM_SC_PS(2);
	TPM1->SC |= TPM_SC_CMOD(1);
	TPM1->MOD = TPM1_MOD;
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // Edge PWM
}
void setup_PTA12(){
	//PTA12 have to use TPM1
	//PTA12 to ALT3 (TPM1_CH0),
	PORTA->PCR[12] = PORT_PCR_MUX(3);
}
void setup_PortB(){
	//PTB2, PTB3 TPM2
	//PTB1, PTB0 right motor
	//PTB0, PTB1 to GPIO, output
	PORTB->PCR[0] |= PORT_PCR_MUX(1);
	PORTB->PCR[1] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= (1<<0) | (1<<1);
	// PTB2 & PTB3 as PWM control
	PORTB->PCR[2] = PORT_PCR_MUX(3);
	PORTB->PCR[3] = PORT_PCR_MUX(3);
}
void setup_TPM2(){
	//set up TPM2 for PWM, OSCERCLK, PS = 1, Clock Mod increment
	TPM2->SC |= TPM_SC_PS(0);
	TPM2->SC |= TPM_SC_CMOD(1);
	TPM2->MOD = TPM2_MOD;
	TPM2->CONTROLS[0].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // Edge PWMA
	TPM2->CONTROLS[1].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // Edge PWMB
}
void setup_PortC(){
	//PTC1, PTC2 to GPIO, output
	PORTC->PCR[1] |= PORT_PCR_MUX(1);
	PORTC->PCR[2] |= PORT_PCR_MUX(1);
	GPIOC->PDDR |= (1<<1) | (1<<2);
	//PTC3 (SW1) to GPIO, pull enable, pull select, input
	PORTC->PCR[3] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
	GPIOC->PDDR &= ~(1<<3); // Clear Data direction (input)
	//PTC12 (SW2) to GPIO, pull enable, pull select, input
	PORTC->PCR[12] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
	GPIOC->PDDR &= ~(1<<12); // Clear Data direction (input)
}
bool SW1_press(){
	return !(GPIOC->PDIR & (1<<3));
}
bool SW2_press(){
	return !(GPIOC->PDIR & (1<<12));
}
void delay(float ms){
	float count = (ms*1e6f/40.0f)-1.0f;
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = count;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN(1); // enable timer
	// Wait until flag is set
	while (!(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK));
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;   // Clear flag
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN(0);   // Stop timer
}

