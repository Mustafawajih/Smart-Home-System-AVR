/*
 * LM35.h
 *
 * Created: 10/7/2023 2:35:49 PM
 *  Author: Musta
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "ADC.h"

void LM35_Init(ADC_InitTypes * options);
u16 LM35_Read(ADC_ChannelTypes ChannelId);



#endif /* LM35_H_ */