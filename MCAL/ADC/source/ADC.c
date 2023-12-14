/*
 * ADC.c
 *
 * Created: 10/7/2023 2:33:43 PM
 *  Author: Musta
 */ 

#include "ADC.h"

void ADC_Init(ADC_InitTypes * options)
{
	adcRegisters->ADC_ADMUX_Reg = (options->adcVref)<<6;
	adcRegisters->ADC_ADCSRA_Reg.AllRegister |= options->adcClock;
	adcRegisters->ADC_ADCSRA_Reg.Bits.ADC_ADEN_Bit =1; 
}
//---------------------------------------------------
u16 ADC_Read(ADC_ChannelTypes channelId)
{
	u16 adcValue = 0;
	adcRegisters->ADC_ADMUX_Reg = (adcRegisters->ADC_ADMUX_Reg & 0b11100000)|(channelId & 0b00011111);
	adcRegisters->ADC_ADCSRA_Reg.Bits.ADC_ADSC_Bit = 1; // start conversion
	while(adcRegisters->ADC_ADCSRA_Reg.Bits.ADC_ADIF_Bit == 0); // waiting the flag
	adcRegisters->ADC_ADCSRA_Reg.Bits.ADC_ADIF_Bit = 1; // clear the flag
	adcValue = adcRegisters->ADC_ADCL_Reg | adcRegisters->ADC_ADCH_Reg<<8;
	return adcValue;
	
}