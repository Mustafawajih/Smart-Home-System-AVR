/*
 * LM35.c
 *
 * Created: 10/7/2023 2:36:02 PM
 *  Author: Musta
 */ 

#include "LM35.h"

void LM35_Init(ADC_InitTypes * options)
{
	ADC_Init(options);
}
u16 LM35_Read(ADC_ChannelTypes ChannelId)
{
	u16 adcValue =0;
	u16 Temp= 0;
	adcValue = ADC_Read(ChannelId);
	Temp = adcValue/4;
	return Temp;
}