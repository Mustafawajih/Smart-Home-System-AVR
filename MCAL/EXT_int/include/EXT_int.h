/*
 * EXT_int.h
 *
 * Created: 10/6/2023 3:57:34 PM
 *  Author: Musta
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "STD.h"
#include "EXT_int_Reg.h"
#include "EXT_int_Type.h"
#include <avr/interrupt.h>


void Ext_Interrupt_Enable(Ext_Int_Types extIntId);
void Ext_Interrupt_Disable(Ext_Int_Types extIntId);
void Ext_Interrupt_SnControl(Ext_Int_Types extIntId, Ext_Int_SnControl mode);
void Ext_Interrupt_SetCallBack(Ext_Int_Types extIntId, void(*ExtIntCopyPtr)(void));



#endif /* EXT_INT_H_ */