/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   DIO.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*
*        Author : Mustafa Wajih Helal
*        Layer  : MCAL
*        SWC    : DIO
*
*___________________________________________________________________________________________________________________________*/ 

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define  SET_BIT(REG, BITNu)	REG |= (1<<BITNu)
#define  CLR_BIT(REG, BITNu)	REG &=~(1<<BITNu)
#define  TOG_BIT(REG, BITNu)	REG ^= (1<<BITNu)
#define  GET_BIT(REG, BITNu)	((REG>>BITNu)&1)


//#define  GET_BIT(REG, BITNu)	REG &= (1<<BITNu)




#endif /*BIT_MATH_H_*/