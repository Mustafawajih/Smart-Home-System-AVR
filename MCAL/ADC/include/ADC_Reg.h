/*
 * ADC_Reg.h
 *
 * Created: 10/7/2023 2:34:11 PM
 *  Author: Musta
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#include "STD.h"
#include "ADC_Types.h"

// #define ADC_ADMUX_Reg (*(volatile u8*)0x27)
// #define ADC_ADCSRA_Reg (*(volatile u8*)0x26)
// #define ADC_ADCH_Reg (*(volatile u8*)0x25)
// #define ADC_ADCL_Reg (*(volatile u8*)0x24)

// #define ADC_ADCSRA_ADEN_Bit 7
// #define ADC_ADCSRA_ADIF_Bit 4
// #define ADC_ADCSRA_ADIE_Bit 3


#define adcRegisters ((volatile ADC_Registers*)0x24)

#endif /* ADC_REG_H_ */