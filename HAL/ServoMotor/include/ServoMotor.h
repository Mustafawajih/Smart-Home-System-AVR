/*
 * ServoMotor.h
 *
 * Created: 10/14/2023 5:06:56 PM
 *  Author: Musta
 */ 


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "Timer1.h"
#include "DIO.h"

#define miniAngle 0
#define maxAngle  180
#define miniCount 250
#define maxCount  500 


void ServoMotor(f32 angle);


#endif /* SERVOMOTOR_H_ */