/*
 * ultrasonic.h
 *
 *  Created on: Oct 30, 2025
 *      Author: Lou
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


//TODO: variable
extern int pulse_width;
extern bool object_close;
//TODO: functions
void send_trigger();
bool get_distant(int distant);
void delay_10us();

#endif /* ULTRASONIC_H_ */
