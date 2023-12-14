/*
 * ADC.h
 *
 * Created: 10/7/2023 2:33:57 PM
 *  Author: Musta
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ADC_Reg.h"
#include "ADC_Types.h"
#include "BIT_MATH.h"


void ADC_Init(ADC_InitTypes * options);
u16 ADC_Read(ADC_ChannelTypes channelId);



#endif /* ADC_H_ */