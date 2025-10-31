/*
 * wheel.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */

#ifndef WHEEL_H_
#define WHEEL_H_
//wheel motor
#define timeTurnLeft 1000
#define timeTurnRight 1000
#define leftSpeed 32000
#define rightSpeed 30750
#define TPM2_MOD 39999
//wheel motor logic
void go_straight();
void turn_left();
void turn_right();
void turn_around();
void stop();
void setMotorSpeed(float left, float right);


#endif /* WHEEL_H_ */
