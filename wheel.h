/*
 * wheel.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */

#ifndef WHEEL_H_
#define WHEEL_H_
//wheel motor
#define timeTurnLeft 500
#define timeTurnRight 500
#define leftSpeed TPM2_MOD
#define rightSpeed leftSpeed*0.88
#define TPM2_MOD 39999
//wheel motor logic
void go_straight();
void turn_left();
void turn_right();
void turn_around();
void stop();
void setMotorSpeed(float left, float right);
//delay
void delay_ms(int ms);

#endif /* WHEEL_H_ */
