/*
 * UART.c
 *
 * Created: 10/21/2023 3:30:12 PM
 *  Author: Musta
 */ 

#include "UART.h"

void UART_Init(UART_ConfigTypes * options)
{
	u16 MyUBRR = 0;
	if(options->doubleSpeedStatus == DoubleSpeed_Enable)
	{
		UART->UCSRA_Reg.Bits.U2X_Bit = 1;
		MyUBRR = (F_CPU/(8UL*options->baudRate))-1;
	}
	else
	{
		UART->UCSRA_Reg.Bits.U2X_Bit = 0;
		MyUBRR = (F_CPU/(16UL*options->baudRate))-1;
	}
	
	UART->UBRRL_Reg = MyUBRR;
	UART->UCSRC_UBRRH_Reg.AllRegister == MyUBRR>>8;
	
	if(options->characterSizeStatus == CharacterSize_9)
	{
		UART->UCSRB_Reg.Bits.UCSZ2_Bit = 1;
// 		UART->UCSRC_UBRRH_Reg.UCSRCBits.UCSZ0_Bit = 1;
// 		UART->UCSRC_UBRRH_Reg.UCSRCBits.UCSZ1_Bit = 1;
		UART->UCSRC_UBRRH_Reg.AllRegister |= UCSRC_SelectEnable | (3<<1);
	}
	else
	{
		UART->UCSRC_UBRRH_Reg.AllRegister |= UCSRC_SelectEnable | options->characterSizeStatus<<1;
	}
	
	UART->UCSRC_UBRRH_Reg.AllRegister |= UCSRC_SelectEnable | options->parityStatus<<4;
	UART->UCSRC_UBRRH_Reg.AllRegister |= UCSRC_SelectEnable | options->stopBitsStatus<<3;
	UART->UCSRB_Reg.AllRegister |= options->txStatus<<3;
	UART->UCSRB_Reg.AllRegister |= options->rxStatus<<4;
	
}
void UART_TransmaitChar(u8 data)
{
	while(UART->UCSRA_Reg.Bits.UDRE_Bit == 0);
	UART->UDR_Reg = data;	
}
void UART_TransmaitString(s8 * string)
{
	u8 i=0;
	while(string[i] != '\0')
	{
		UART_TransmaitChar(string[i]);
		i++;
	}
	
}
u8 UART_Receive()
{
	while(UART->UCSRA_Reg.Bits.RXC_Bit == 0);
//  	if(UART->UCSRA_Reg.Bits.RXC_Bit == 0)
//  	{
//  		if(UART->UCSRA_Reg.Bits.RXC_Bit == 0)
//  		{
//  			
//  		}
//  	}
	return UART->UDR_Reg;
}

 void UART_voidReceiveStringSync_Rx(u8 * Copy_u8ReceiveData){
	 u8 counter =0;
	 volatile u8 recChar;
	 recChar =  UART_Receive();
	 if(Copy_u8ReceiveData != 0){
		 while(recChar !=13){
			 UART_TransmaitChar(recChar);
			 //read data
			 Copy_u8ReceiveData[counter]= recChar;
			 counter ++ ;
			 recChar =  UART_Receive();
			 
		 }
	 }
 }
