/*
 * Bluetooth.h
 *
 * Created: 10/21/2023 4:40:41 PM
 *  Author: Musta
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "UART.h"

void Bluetooth_Init(UART_ConfigTypes * options);
void Bluetooth_TransmaitChar(u8 data);
void Bluetooth_TransmaitString(s8 * string);
u8 Bluetooth_Receive();



#endif /* BLUETOOTH_H_ */