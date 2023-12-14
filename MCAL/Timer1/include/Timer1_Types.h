/*
 * Timer1_Types.h
 *
 * Created: 10/14/2023 2:02:52 PM
 *  Author: Musta
 */ 


#ifndef TIMER1_TYPES_H_
#define TIMER1_TYPES_H_

#include "STD.h"

typedef struct{
	 
	 u8 WGM10_Bit:1;
	 u8 WGM11_Bit:1;	
	 u8 FOC1B_Bit:1;
	 u8 FOC1A_Bit:1;
	 u8 COM1B0_Bit:1;
	 u8 COM1B1_Bit:1;
	 u8 COM1A0_Bit:1;
	 u8 COM1A1_Bit:1;
		 
}TCCR1A_Bits;


typedef struct{
	
	u8 CS10_Bit:1;
	u8 CS11_Bit:1;
	u8 CS12_Bit:1;
	u8 WGM12_Bit:1;
	u8 WGM13_Bit:1;
	u8 RESERVED_Bit:1;
	u8 ICES1_Bit:1;
	u8 ICNC1_Bit:1;
	
}TCCR1B_Bits;

typedef struct{
	
	u8 TOV0_Bit:1;
	u8 OCF0_Bit:1;
	u8 TOV1_Bit:1;
	u8 OCF1B_Bit:1;
	u8 OCF1A_Bit:1;
	u8 ICF1_Bit:1;
	u8 TOV2_Bit:1;
	u8 OCF2_Bit:1;
	
}TIFR_Bits;

//--------------------------------------------------------------
typedef union{
	
	u8 AllRegister;
	TCCR1A_Bits Bits;
	
}TCCR1A_RegisterType;


typedef union{
	
	u8 AllRegister;
	TCCR1B_Bits Bits;
	
}TCCR1B_RegisterType;


typedef union{
	
	u8 AllRegister;
	TIFR_Bits Bits;
	
}TIFR_RegisterType;

//-----------------------------------------------------
typedef struct{

	u16 ICR1_Reg;
	u16 OCR1B_Reg;
	u16 OCR1A_Reg;
	u16 TCNT1_Reg;
	TCCR1B_RegisterType TCCR1B_Reg;
	TCCR1A_RegisterType TCCR1A_Reg;
	u8 Reserved[8];
	TIFR_RegisterType TIFR_Reg;
	u8 TIMSK_Reg; 
	
}Timer1_Registers;

//-------------------------------------------------
typedef enum{
	
	Normal=0,
	CTC=4,
	PWM_Phase_Correct=10,
	PWM_Fast=14
			
}Timer1_ModeTypes;


typedef enum{
	
	No_Clock=0,
	No_Prescalling,
	Clock_8,
	Clock_64,
	Clock_256,
	Clock_1024,
	Clock_Ext_Falling,
	Clock_Ext_Rising
	
}Timer1_ClockTypes;


typedef enum{
	
	COM1A_No_PWM=0,
	COM1A_Non_Inverting_PWM=2,
	COM1A_Inverting_PWM
		
}Timer1_COM1APWMTypes;


typedef enum{
	
	COM1B_No_PWM=0,
	COM1B_Non_Inverting_PWM=2,
	COM1B_Inverting_PWM
	
}Timer1_COM1BPWMTypes;


typedef enum{
	
	TOVInt_Disable=0,
	TOVInt_Enable
	
}Timer1_TOVIntTypes;

typedef enum{
	
	OC1AInt_Disable=0,
	OC1AInt_Enable
	
}Timer1_OC1AIntTypes;

typedef enum{
	
	OC1BInt_Disable=0,
	OC1BInt_Enable
	
}Timer1_OC1BIntTypes;

typedef enum{
	
	ICInt_Disable=0,
	ICInt_Enable
	
}Timer1_ICIntTypes;
//-----------------------------------------------------------
typedef struct{
	
	Timer1_ModeTypes Mode;
	Timer1_ClockTypes Prescaler;
	Timer1_COM1APWMTypes COM1APWMTMode;
	Timer1_COM1BPWMTypes COM1BPWMTMode;
	Timer1_TOVIntTypes  TOVIntStatus;
	Timer1_OC1AIntTypes OC1AIntStatus;
	Timer1_OC1BIntTypes OC1BIntStatus;
	Timer1_ICIntTypes ICIntStatus;
	
}Timer1_InitTypes;

typedef enum{
	
	TOVInt=0,
	OC1AInt,
	OC1BInt,
	ICInt
		
}Timer1_InterruptTypes;


typedef enum{
	
	OCR1A_DataReg=0,
	OCR1B_DataReg,
	ICR1_DataReg
		
}Timer1_DataRegTypes;



#endif /* TIMER1_TYPES_H_ */