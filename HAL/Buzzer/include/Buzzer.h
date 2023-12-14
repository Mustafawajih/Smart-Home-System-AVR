/*
 * Buzzer.h
 *
 * Created: 12/6/2023 4:38:56 PM
 *  Author: Musta
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "DIO.h"

#define  Buzzer_Pin    DIO_ChannelB4

//prototype
void Buzzer_void_init();
void Buzzer_void_ON  ();
void Buzzer_void_OFF ();
 


#endif /* BUZZER_H_ */