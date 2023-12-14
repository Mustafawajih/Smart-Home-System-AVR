/*
 * UART.h
 *
 * Created: 10/21/2023 3:29:50 PM
 *  Author: Musta
 */ 


#ifndef UART_H_
#define UART_H_

#include "UART_Reg.h"
#include "Clock.h"

void UART_Init(UART_ConfigTypes * options);
void UART_TransmaitChar(u8 data);
void UART_TransmaitString(s8 * string);
u8 UART_Receive();
void UART_voidReceiveStringSync_Rx(u8 * Copy_u8ReceiveData);



#endif /* UART_H_ */