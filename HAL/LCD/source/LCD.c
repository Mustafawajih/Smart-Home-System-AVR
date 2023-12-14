/*
* LCD.c
*
* Created: 9/29/2023 2:24:39 PM
*  Author: Musta
*/
#include "LCD.h"

void LCD_Init()
{
	DIO_ConfigChannel(DIO_ChannelA4, DIO_OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA5, DIO_OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA6, DIO_OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA7, DIO_OUTPUT);

	DIO_ConfigChannel(DIO_ChannelB1, DIO_OUTPUT);
	DIO_ConfigChannel(DIO_ChannelB2, DIO_OUTPUT);
	DIO_ConfigChannel(DIO_ChannelB5, DIO_OUTPUT);

	DIO_WriteChannel(DIO_ChannelA4, STD_HIGH);
	DIO_WriteChannel(DIO_ChannelA5, STD_HIGH);
	DIO_WriteChannel(DIO_ChannelA6, STD_HIGH);
	DIO_WriteChannel(DIO_ChannelA7, STD_HIGH);
			
	DIO_WriteChannel(LCD_RW, STD_LOW);
	DIO_WriteChannel(LCD_E, STD_HIGH);
	_delay_ms(20);
	LCD_Cmd(0x33);
	LCD_Cmd(0x32);
	
	LCD_Cmd(0x28); // function set 4bit  & 2line & 5*8
	LCD_Cmd(0x06); //entry mode to right
	LCD_Cmd(0x0C); // display on & cursor  
	
}
//-------------------------------------------------------
void LCD_Cmd (u8 cmd)
{
	u8 portValue= STD_LOW;
	DIO_WriteChannel(LCD_RS, STD_LOW);
	portValue=DIO_ReadPort(LCD_DataPort);
	portValue=(portValue & 0x0F) | (cmd & 0xF0) ;
	DIO_WritePort(LCD_DataPort, portValue);
	DIO_WriteChannel(LCD_E, STD_LOW);
	_delay_us(100);
	DIO_WriteChannel(LCD_E, STD_HIGH);
	
	_delay_ms(5);
	
	portValue=DIO_ReadPort(LCD_DataPort);
	portValue=(portValue & 0x0F) | (cmd<<4) ;
	DIO_WritePort(LCD_DataPort, portValue);
	DIO_WriteChannel(LCD_E, STD_LOW);
	_delay_us(100);
	DIO_WriteChannel(LCD_E, STD_HIGH);
	_delay_ms(2);
	
}
//-----------------------------------------------------------
void LCD_Char (u8 data)
{
	u8 portValue= STD_LOW;
	DIO_WriteChannel(LCD_RS, STD_HIGH);
	portValue=DIO_ReadPort(LCD_DataPort);
	portValue=(portValue & 0x0F) | (data & 0xF0) ;
	DIO_WritePort(LCD_DataPort, portValue);
	DIO_WriteChannel(LCD_E, STD_LOW);
	_delay_us(100);
	DIO_WriteChannel(LCD_E, STD_HIGH);
	
	_delay_ms(5);
	
	portValue=DIO_ReadPort(LCD_DataPort);
	portValue=(portValue & 0x0F) | (data<<4) ;
	DIO_WritePort(LCD_DataPort, portValue);
	DIO_WriteChannel(LCD_E, STD_LOW);
	_delay_us(100);
	DIO_WriteChannel(LCD_E, STD_HIGH);
	_delay_ms(2);
}
//--------------------------------------------------------------
void LCD_String ( s8 * string)
{
	u8 i = 0;
	while(string[i] != '\0')
	{
		LCD_Char(string[i]);
		i++;
	}
}
//---------------------------------------------------------------
void LCD_Number(u32 num)
{
	u32 Loc_u32Reversed=1;
	
	if(num == 0)
	{
		LCD_Char('0');
	} 
	else
	{
		while(num != 0)
		{
			Loc_u32Reversed=(Loc_u32Reversed * 10) + (num % 10);
			num /= 10;
		}
		while(Loc_u32Reversed != 1)
		{
			LCD_Char((Loc_u32Reversed % 10) + 48);
			Loc_u32Reversed /= 10;
		}
	}
}
//----------------------------------------------------
void LCD_Clear()
{
	LCD_Cmd(0x01);
}
//---------------------------------------------------

void LCD_Setpos(u8 line, u8 pos)
{
	switch(line)
	{
		case 1:
		LCD_Cmd(0x80 | (pos & 0x0F));
		break;
		case 2:
		LCD_Cmd(0xC0 | (pos & 0x0F));
		break;
	}
}
//---------------------------------------------------------

void LCD_Custom_Char(u8 loc, s8 * msg)
{
	if(loc < 8)
	{
		LCD_Cmd(0x40 + (loc*8));
		for(u8 i=0; i<8; i++)
		{
			LCD_Char(msg[i]);
		}
		
	}
}
//-----------------------------------------------------------