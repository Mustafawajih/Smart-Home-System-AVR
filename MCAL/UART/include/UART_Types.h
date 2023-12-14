/*
 * UART_Types.h
 *
 * Created: 10/21/2023 3:29:13 PM
 *  Author: Musta
 */ 


#ifndef UART_TYPES_H_
#define UART_TYPES_H_

#include "STD.h"


#define UCSRC_SelectEnable (1<<7)

typedef struct{

	u8 MPCM_Bit:1;
	u8 U2X_Bit:1;
	u8 PE_Bit:1;
	u8 DOR_Bit:1;
	u8 FE_Bit:1;
	u8 UDRE_Bit:1;
	u8 TXC_Bit:1;
	u8 RXC_Bit:1;
	
}UCSRA_Bits;

typedef struct{

	u8 TXB8_Bit:1;
	u8 RXB8_Bit:1;
	u8 UCSZ2_Bit:1;
	u8 TXEN_Bit:1;
	u8 RXEN_Bit:1;
	u8 UDRIE_Bit:1;
	u8 TXCIE_Bit:1;
	u8 RXCIE_Bit:1;
	
}UCSRB_Bits;

typedef struct{

	u8 UCPOL_Bit:1;
	u8 UCSZ0_Bit:1;
	u8 UCSZ1_Bit:1;
	u8 USBS_Bit:1;
	u8 UPM0_Bit:1;
	u8 UPM1_Bit:1;
	u8 UMSEL_Bit:1;
	u8 URSEL_Bit:1;
	
}UCSRC_Bits;


typedef union{
	
	u8 AllRegister;
	UCSRA_Bits Bits;
	
}UCSRCA_Type;

typedef union{
	
	u8 AllRegister;
	UCSRB_Bits Bits;
	
}UCSRCB_Type;

typedef union{
	
	u8 AllRegister;
	UCSRC_Bits UCSRCBits;
	
}UCSRC_UBRRH_Type;


typedef struct{
	
	u8 UBRRL_Reg;
	UCSRCB_Type UCSRB_Reg;
	UCSRCA_Type UCSRA_Reg;
	u8 UDR_Reg;
	u8 RESERVED[19];
	UCSRC_UBRRH_Type UCSRC_UBRRH_Reg;
		
}UART_Register;


typedef enum{
	
	BaudRate_2400=2400,
	BaudRate_4800=4800,
	BaudRate_9600=9600
		
}UART_BaudRateTypes;


typedef enum{
	
	Stop_1Bit=0,
	Stop_2Bit
	
}UART_StopTypes;

typedef enum{
	
	CharacterSize_5=0,
	CharacterSize_6,	
	CharacterSize_7,
	CharacterSize_8,
	CharacterSize_9=7
	
}UART_CharacterSizeTypes;

typedef enum{
	
	Parity_Disable=0,
	Parity_Reserved,
	Parity_Even,
	Parity_Odd
	
}UART_ParityTypes;


typedef enum{
	
	TX_Disable=0,
	TX_Enable
	
}UART_TxTypes;

typedef enum{
	
	RX_Disable=0,
	RX_Enable
	
}UART_RxTypes;

typedef enum{
	
	DoubleSpeed_Disable=0,
	DoubleSpeed_Enable
	
}UART_DoubleSpeedType;

typedef struct{
	
	UART_BaudRateTypes  baudRate;
	UART_DoubleSpeedType doubleSpeedStatus;
	UART_CharacterSizeTypes characterSizeStatus;
	UART_StopTypes stopBitsStatus;
	UART_ParityTypes parityStatus;
	UART_TxTypes txStatus;
	UART_RxTypes rxStatus;
	
}UART_ConfigTypes;


#endif /* UART_TYPES_H_ */