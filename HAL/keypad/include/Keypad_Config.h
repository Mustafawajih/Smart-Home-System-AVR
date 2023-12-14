/*
 * Keypad_Config.h
 *
 * Created: 9/30/2023 1:32:33 PM
 *  Author: Musta
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define r0 DIO_ChannelA2
#define r1 DIO_ChannelA3
#define r2 DIO_ChannelC2
#define r3 DIO_ChannelC3


#define c0 DIO_ChannelC4
#define c1 DIO_ChannelC5
#define c2 DIO_ChannelC6
#define c3 DIO_ChannelC7

#define rowsCount   4
#define colsCount   4

DIO_ChanelTypes  KeypadRows[rowsCount]={r0,r1,r2,r3};
DIO_ChanelTypes  KeypadCols[colsCount]={c0,c1,c2,c3};

u8 Keypad[rowsCount][colsCount] = {{'7','8','9','/'},
								   {'4','5','6','*'},
								   {'1','2','3','-'},
								   {'C','0','=','+'}};      
										
										
#endif /* KEYPAD_CONFIG_H_ */