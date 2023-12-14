/*
 * LCD.h
 *
 * Created: 9/29/2023 2:24:26 PM
 *  Author: Musta
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Clock.h"
#include "DIO.h"


#define LCD_RS   DIO_ChannelB1
#define LCD_RW	 DIO_ChannelB2
#define LCD_E	 DIO_ChannelB5

#define LCD_DataPort   DIO_PortA 

void LCD_Init();
void LCD_Cmd (u8 cmd);
void LCD_Char (u8 data);
void LCD_String ( s8 * string);
void LCD_Number(u32 num);
void LCD_Clear();
void LCD_Setpos(u8 line, u8 pos);
void LCD_Custom_Char(u8 loc, s8 * msg);

#endif /* LCD_H_ */