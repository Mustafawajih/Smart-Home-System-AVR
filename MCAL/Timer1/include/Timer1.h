/*
 * Timer1.h
 *
 * Created: 10/14/2023 2:03:06 PM
 *  Author: Musta
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "Timer1_Reg.h"
#include <avr/interrupt.h>

void Timer1_Init(Timer1_InitTypes* options);
void Timer1_SetCallBack(Timer1_InterruptTypes interruptId, void (*IntCopyFunPtr)(void));
void Timer1_SetValue(Timer1_DataRegTypes dataRegister, u16 dataValue);



#endif /* TIMER1_H_ */