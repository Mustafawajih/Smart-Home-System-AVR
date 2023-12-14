/*
 * Motor.c
 *
 * Created: 12/9/2023 3:39:03 PM
 *  Author: Musta
 */ 

#include "Motor.h"

void MotorInit()
{
	DIO_ConfigChannel(Motor_pin,DIO_OUTPUT);
}
void Motor_ON ()
{
	DIO_WriteChannel(Motor_pin,STD_HIGH);
}
void Motor_OFF()
{
	DIO_WriteChannel(Motor_pin,STD_LOW);
}