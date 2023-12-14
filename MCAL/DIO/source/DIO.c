/*
* DIO.c
*
* Created: 9/23/2023 3:12:15 PM
*  Author: Musta
*/

#include "DIO.h"
#include "Clock.h"


void DIO_WriteChannel(DIO_ChanelTypes ChannelId, STD_level_Type Level)
{
	
	DIO_PortType Portx = ChannelId/8;
	DIO_ChanelTypes BITNu = ChannelId%8;
	
	switch(Portx)
	{
		case DIO_PortA:
		if(Level == STD_HIGH)
		{
			SET_BIT(PORTA_Reg, BITNu);
		}
		else
		{
			CLR_BIT(PORTA_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortB:
		if(Level == STD_HIGH)
		{
			SET_BIT(PORTB_Reg, BITNu);
		}
		else
		{
			CLR_BIT(PORTB_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortC:
		if(Level == STD_HIGH)
		{
			SET_BIT(PORTC_Reg, BITNu);
		}
		else
		{
			CLR_BIT(PORTC_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortD:
		if(Level == STD_HIGH)
		{
			SET_BIT(PORTD_Reg, BITNu);
		}
		else
		{
			CLR_BIT(PORTD_Reg, BITNu);
			
		}
		break;
		
	}
	
}

//---------------------------------------------------------------------------------------------------

void DIO_ConfigChannel(DIO_ChanelTypes ChannelId, DIO_DirType Direction)
{
	
	DIO_PortType Portx = ChannelId/8;
	DIO_ChanelTypes BITNu = ChannelId%8;
	
	switch(Portx)
	{
		case DIO_PortA:
		if(Direction == DIO_OUTPUT)
		{
			SET_BIT(DDRA_Reg, BITNu);
		}
		else
		{
			CLR_BIT(DDRA_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortB:
		if(Direction == DIO_OUTPUT)
		{
			SET_BIT(DDRB_Reg, BITNu);
		}
		else
		{
			CLR_BIT(DDRB_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortC:
		if(Direction == DIO_OUTPUT)
		{
			SET_BIT(DDRC_Reg, BITNu);
		}
		else
		{
			CLR_BIT(DDRC_Reg, BITNu);
			
		}
		break;
		
		case DIO_PortD:
		if(Direction == DIO_OUTPUT)
		{
			SET_BIT(DDRD_Reg, BITNu);
		}
		else
		{
			CLR_BIT(DDRD_Reg, BITNu);
			
		}
		break;
		
	}
}
//---------------------------------------------------------------------------------------------------------

STD_level_Type DIO_ReadChannel(DIO_ChanelTypes ChannelId)
{
	STD_level_Type result=STD_LOW;
	DIO_PortType Portx = ChannelId/8;
	DIO_ChanelTypes BITNu = ChannelId%8;
	
	switch(Portx)
	{
		case DIO_PortA:
		result= GET_BIT(PINA_Reg, BITNu);
		break;
		
		case DIO_PortB:
		result= GET_BIT(PINB_Reg, BITNu);
		break;
		
		case DIO_PortC:
		result= GET_BIT(PINC_Reg, BITNu);
		break;
		
		case DIO_PortD:
		result= GET_BIT(PIND_Reg, BITNu);
		break;
	}
	
	return result;
	
}
//------------------------------------------------------------------------------------------------
void DIO_ToggleChannel(DIO_ChanelTypes ChannelId)
{
	DIO_PortType Portx = ChannelId/8;
	DIO_ChanelTypes BITNu = ChannelId%8;
	
	switch(Portx)
	{
		case DIO_PortA:
		TOG_BIT(PORTA_Reg, BITNu);break;
		case DIO_PortB:
		TOG_BIT(PORTB_Reg, BITNu);break;
		case DIO_PortC:
		TOG_BIT(PORTC_Reg, BITNu);break;
		case DIO_PortD:
		TOG_BIT(PORTD_Reg, BITNu);break;
	}
	
}
//----------------------------------------------------------------------------------------
u8 DIO_ReadPort(DIO_PortType portId)
{
	u8 portValue=STD_LOW;
	switch(portId)
	{
		case DIO_PortA:
		portValue = PORTA_Reg;
		break;
		
		case DIO_PortB:
		portValue = PORTB_Reg;
		break;
		
		case DIO_PortC:
		portValue = PORTC_Reg;
		break;
		
		case DIO_PortD:
		portValue = PORTD_Reg;
		break;
	}
	
	return portValue;
}
//-------------------------------------------------------------------------

void DIO_WritePort(DIO_PortType portId, u8 portValue)
{
	switch(portId)
	{
		case DIO_PortA:
		PORTA_Reg = portValue ;
		break;
		case DIO_PortB:
		PORTB_Reg = portValue;
		break;
		case DIO_PortC:
		PORTC_Reg  = portValue;
		break;
		case DIO_PortD:
		PORTD_Reg = portValue;
		break;
	}
}

//-----------------------------------------------------------------------------

void DIO_WriteChannelGroup(DIO_PortType portId, u8 portValue, u8 mask)
{
	switch(portId)
	{
		case DIO_PortA:
		PORTA_Reg = (PORTA_Reg & ~mask) | (portValue & mask);
		break;
		case DIO_PortB:
		PORTB_Reg = (PORTB_Reg & ~mask) | (portValue & mask);
		break;
		case DIO_PortC:
		PORTC_Reg = (PORTC_Reg & ~mask) | (portValue & mask);
		break;
		case DIO_PortD:
		PORTD_Reg = (PORTD_Reg & ~mask) | (portValue & mask);
		break;
	}
}