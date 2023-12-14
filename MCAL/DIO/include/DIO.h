/*
 * DIO.h
 *
 * Created: 9/23/2023 3:08:21 PM
 *  Author: Musta
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "BIT_MATH.h"
#include "STD.h"
#include "DIO_Reg.h"
#include "DIO_Types.h"


void DIO_WriteChannel(DIO_ChanelTypes ChannelId, STD_level_Type Level);
void DIO_ConfigChannel(DIO_ChanelTypes ChannelId, DIO_DirType Direction);
STD_level_Type DIO_ReadChannel(DIO_ChanelTypes ChannelId);
void DIO_ToggleChannel(DIO_ChanelTypes ChannelId);
u8 DIO_ReadPort(DIO_PortType portId);
void DIO_WritePort(DIO_PortType portId, u8 portValue);
void DIO_WriteChannelGroup(DIO_PortType portId, u8 portValue, u8 mask);


#endif /* DIO_H_ */