/*
 * DIO_Reg.h
 *
 * Created: 9/23/2023 1:57:12 PM
 *  Author: Musta
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_


#define PORTA_Reg   (*((volatile u8*)0x3B))
#define DDRA_Reg    (*((volatile u8*)0x3A))
#define PINA_Reg    (*((volatile u8*)0x39))

#define PORTB_Reg   (*((volatile u8*)0x38))
#define DDRB_Reg    (*((volatile u8*)0x37))
#define PINB_Reg    (*((volatile u8*)0x36))

#define PORTC_Reg   (*((volatile u8*)0x35))
#define DDRC_Reg    (*((volatile u8*)0x34))
#define PINC_Reg    (*((volatile u8*)0x33))

#define PORTD_Reg   (*((volatile u8*)0x32))
#define DDRD_Reg    (*((volatile u8*)0x31))
#define PIND_Reg    (*((volatile u8*)0x30))




#endif /* DIO_REG_H_ */