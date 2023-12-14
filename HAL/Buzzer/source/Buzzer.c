/*
 * Buzzer.c
 *
 * Created: 12/6/2023 4:39:08 PM
 *  Author: Musta
 */ 


#include "Buzzer.h"

void Buzzer_void_init()
{
	DIO_ConfigChannel(Buzzer_Pin,DIO_OUTPUT);
}
void Buzzer_void_ON()
{
	DIO_WriteChannel(Buzzer_Pin,STD_HIGH);
}
void Buzzer_void_OFF()
{
	DIO_WriteChannel(Buzzer_Pin,STD_LOW);
}