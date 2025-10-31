/*
 * function.h
 *
 *  Created on: Oct 29, 2025
 *      Author: Lou
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

//ultrasonic

//Configuration
void setup_SIM_SCGC5();
void setup_SIM_SCGC6();
void setup_SOPT2();
void setup_TPM0();
void setup_TPM2();
void setup_PIT();
void PIT_IRQHandler();
void PORTA_IRQHandler();
void setup_Wheel();
void setup_PortB();
void setup_PortC();
void setup_Servo();
void setup_TPM1();
void setup_PTA12();
void setup_Ultrasound();
void setup_PTA13();
void setup_PTD2();

//delays
void delay(float ms);

bool obstableClose();
bool obstableFar();

//switch logic
bool SW1_press();
bool SW2_press();
#endif /* FUNCTION_H_ */
