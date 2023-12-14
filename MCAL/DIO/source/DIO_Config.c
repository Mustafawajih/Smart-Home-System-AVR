/*
* DIO_Config.c
*
* Created: 9/23/2023 4:36:36 PM
*  Author: Musta
*/

#include "DIO_Config.h"


DIO_PinCfg pinCfg[]={
	
	//PORTA
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
		
	//PORTB
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
		
	//PORTC
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	
	//PORTD
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	{DIO_INPUT , STD_LOW },
	{DIO_OUTPUT, STD_HIGH},
	{DIO_OUTPUT, STD_HIGH},
	
	
};

//-----------------------------------------------------------------------------

void DIO_Init()
{
	DIO_PortType Portx;
	DIO_ChanelTypes BITNu;
	
	DIO_ChanelTypes Count = DIO_ChannelA0;
	
	for(Count = DIO_ChannelA0; Count < PINCOUNT; Count++)
	{
		Portx= Count/8;
		BITNu= Count%8;
		
		switch(Portx)
		{
			case DIO_PortA:
			if(pinCfg[Count].direction == DIO_OUTPUT)
			{
				SET_BIT(DDRA_Reg, BITNu);
			}
			else
			{
				CLR_BIT(DDRA_Reg, BITNu);
				
			}
			break;
			
			case DIO_PortB:
			if(pinCfg[Count].direction == DIO_OUTPUT)
			{
				SET_BIT(DDRB_Reg, BITNu);
			}
			else
			{
				CLR_BIT(DDRB_Reg, BITNu);
				
			}
			break;
			
			case DIO_PortC:
			if(pinCfg[Count].direction == DIO_OUTPUT)
			{
				SET_BIT(DDRC_Reg, BITNu);
			}
			else
			{
				CLR_BIT(DDRC_Reg, BITNu);
				
			}
			break;
			
			case DIO_PortD:
			if(pinCfg[Count].direction == DIO_OUTPUT)
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
	
	
}