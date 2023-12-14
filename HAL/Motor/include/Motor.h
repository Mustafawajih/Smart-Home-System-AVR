/*
 * Motor.h
 *
 * Created: 12/9/2023 3:38:51 PM
 *  Author: Musta
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "DIO.h"

#define Motor_pin	DIO_ChannelD2

//prototype

void MotorInit();
void Motor_ON ();
void Motor_OFF();


#endif /* MOTOR_H_ */