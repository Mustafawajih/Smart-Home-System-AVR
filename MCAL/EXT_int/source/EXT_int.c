/*
 * EXT_int.c
 *
 * Created: 10/6/2023 3:58:15 PM
 *  Author: Musta
 */ 

#include "EXT_int.h"

void (*ExtInt0FunPtr)(void) = 0;
void (*ExtInt1FunPtr)(void) = 0;
void (*ExtInt2FunPtr)(void) = 0;


void Ext_Interrupt_Enable(Ext_Int_Types extIntId)
{
	switch(extIntId)
	{
		case Ext_INT0:
		SET_BIT(Ext_Int_GICR_Reg,6);
		break;
		
		case Ext_INT1:
		SET_BIT(Ext_Int_GICR_Reg,7);
		break;
		
		case Ext_INT2:
		SET_BIT(Ext_Int_GICR_Reg,5);
		break;
	}
}
//---------------------------------------------------------------
void Ext_Interrupt_Disable(Ext_Int_Types extIntId)
{
	switch(extIntId)
	{
		case Ext_INT0:
		CLR_BIT(Ext_Int_GICR_Reg,6);
		break;
		
		case Ext_INT1:
		CLR_BIT(Ext_Int_GICR_Reg,7);
		break;
		
		case Ext_INT2:
		CLR_BIT(Ext_Int_GICR_Reg,5);
		break;
	}
}
//------------------------------------------------------------------
void Ext_Interrupt_SnControl(Ext_Int_Types extIntId, Ext_Int_SnControl mode)
{
	switch(extIntId)
	{
		case Ext_INT0:
		Ext_Int_MCUCR_Reg |= (mode<<0);
		break;
		
		case Ext_INT1:
		Ext_Int_MCUCR_Reg |= (mode<<2);
		break;
		
		case Ext_INT2:
		if(mode == Falling_Edge)
		{
			CLR_BIT(Ext_Int_MCUCSR_Reg,6);
		}
		else if(mode == Rising_Edge)
		{
			SET_BIT(Ext_Int_MCUCSR_Reg,6);
		}
		else
		{
			// Do nothing
		}
		break;
	}
}
void Ext_Interrupt_SetCallBack(Ext_Int_Types extIntId, void(*ExtIntCopyPtr)(void))
{
	switch(extIntId)
	{
		case Ext_INT0:
		ExtInt0FunPtr = ExtIntCopyPtr;
		break;
		
		case Ext_INT1:
		ExtInt1FunPtr = ExtIntCopyPtr;
		break;
		
		case Ext_INT2:
		ExtInt2FunPtr = ExtIntCopyPtr;
		break;
		
	}
	
}
//---------------------------------------------------

ISR(INT0_vect)
{
	ExtInt0FunPtr();
}

ISR(INT1_vect)
{
	ExtInt1FunPtr();
}

ISR(INT2_vect)
{
	ExtInt2FunPtr();
}