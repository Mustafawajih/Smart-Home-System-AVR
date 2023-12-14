/*
 * EXT_int_Reg.h
 *
 * Created: 10/6/2023 3:57:09 PM
 *  Author: Musta
 */ 


#ifndef EXT_INT_REG_H_
#define EXT_INT_REG_H_

#include "BIT_MATH.h"

#define Ext_Int_GIFR_Reg (*(volatile u8*)0x5A)
#define Ext_Int_GICR_Reg (*(volatile u8*)0x5B)
#define Ext_Int_MCUCR_Reg (*(volatile u8*)0x55)
#define Ext_Int_MCUCSR_Reg (*(volatile u8*)0x54)


#endif /* EXT_INT_REG_H_ */