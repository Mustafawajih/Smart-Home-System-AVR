/*
 * TWI_Types.h
 *
 * Created: 10/28/2023 4:06:25 PM
 *  Author: Musta
 */ 


#ifndef TWI_TYPES_H_
#define TWI_TYPES_H_

#include "STD.h"

typedef struct{
	u8 TWIE_Bit:1;
	u8 Reserved_Bit:1;
	u8 TWEN_Bit:1;
	u8 TWWC_Bit:1;
	u8 TWSTO_Bit:1;
	u8 TWSTA_Bit:1;
	u8 TWEA_Bit:1;
	u8 TWINT_Bit:1;	
}TWCR_Bits;

typedef union{
	u8 AllRegister;
	TWCR_Bits Bits;
}TWCR_RegisterType;

typedef struct{
	u8	TWBR_Reg;
	u8	TWSR_Reg;
	u8	TWAR_Reg;
	u8	TWDR_Reg;
	u8	RESERVED[50];
	TWCR_RegisterType TWCR_Reg;	
}TWI_RegistersType;


#endif /* TWI_TYPES_H_ */