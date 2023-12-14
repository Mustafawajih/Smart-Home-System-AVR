/*
 * Bluetooth.c
 *
 * Created: 10/21/2023 4:40:58 PM
 *  Author: Musta
 */ 

#include "Bluetooth.h"

void Bluetooth_Init(UART_ConfigTypes * options)
{
	UART_Init(options);
}
void Bluetooth_TransmaitChar(u8 data)
{
	UART_TransmaitChar(data);
}
void Bluetooth_TransmaitString(s8 * string)
{
	UART_TransmaitString(string);
}
u8 Bluetooth_Receive()
{
	return UART_Receive();
}