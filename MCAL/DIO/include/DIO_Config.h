/*
 * DIO_Config.h
 *
 * Created: 9/23/2023 4:45:01 PM
 *  Author: Musta
 */ 


#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_

#include "DIO.h"

typedef struct{
	DIO_DirType direction;
	STD_level_Type Level;
	
}DIO_PinCfg;
	
	
#define PINCOUNT 32	



void DIO_Init();



#endif /* DIO_CONFIG_H_ */