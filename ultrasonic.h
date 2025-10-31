/*
 * ultrasonic.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
extern int pulse_width;
//TODO: variable
bool object_close();
//TODO: functions
void send_trigger();
bool get_distant();
void delay_10us();

#endif /* ULTRASONIC_H_ */
