/*
 * Keypad.c
 *
 * Created: 9/30/2023 1:35:04 PM
 *  Author: Musta
 */ 
#include "keypad.h"
#include "Keypad_Config.h"

void Keypad_Init()
{
	// cols input
	
	for(u8 j=0; j<colsCount; j++)
	{
		DIO_ConfigChannel(KeypadCols[j], DIO_INPUT);
		DIO_WriteChannel (KeypadCols[j], STD_HIGH);	// connect pull up res 
	}
	for(u8 i=0; i<rowsCount; i++)
	{
		DIO_ConfigChannel(KeypadRows[i], DIO_OUTPUT);
		DIO_WriteChannel (KeypadRows[i], STD_HIGH);
	}
	
}

//-----------------------------------------------------------

u8 GetKey()
{
	for(u8 i=0; i<rowsCount; i++)
	{
		DIO_WriteChannel(KeypadRows[i],STD_LOW);
		for(u8 j=0; j<colsCount; j++)
		{
			if(DIO_ReadChannel(KeypadCols[j])==STD_LOW)
			{
				while(DIO_ReadChannel(KeypadCols[j])==STD_LOW);
				return Keypad[i][j];
			}
		} 
		
		DIO_WriteChannel(KeypadRows[i],STD_HIGH);
	}
	
	return STD_LOW;
}

