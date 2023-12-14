/*
 * Dimmer.h
 *
 * Created: 12/10/2023 10:32:06 PM
 *  Author: Musta
 */ 


#ifndef DIMMER_H_
#define DIMMER_H_
#include <avr/io.h>
#include "Timer1.h"
#include "DIO.h"

#define LED_PIN DIO_ChannelD4
void initPWM();
void setPWM(uint16_t dutyCycle);


#endif /* DIMMER_H_ */