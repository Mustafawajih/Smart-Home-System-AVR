/*
 * ServoMotor.c
 *
 * Created: 10/14/2023 5:07:14 PM
 *  Author: Musta
 */ 


#include "ServoMotor.h"

void ServoMotor(f32 angle)
{
	DIO_ConfigChannel(DIO_ChannelD5, DIO_OUTPUT);
	f32 OCR1AValue = (f32)((angle-miniAngle)*((f32)(maxCount-miniCount)/(maxAngle-miniAngle)))+miniCount-1;
	f32 ICR1Value =4999;
	Timer1_SetValue(ICR1_DataReg,ICR1Value);
	Timer1_SetValue(OCR1A_DataReg,OCR1AValue);
	
	Timer1_InitTypes options ={PWM_Fast,Clock_64,COM1A_Non_Inverting_PWM,COM1B_No_PWM,TOVInt_Disable,OC1BInt_Disable,OC1AInt_Disable,ICInt_Disable };
	Timer1_Init(&options);	
		
}