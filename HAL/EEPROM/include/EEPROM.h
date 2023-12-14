/*
 * EEPROM.h
 *
 * Created: 10/30/2023 8:14:27 PM
 *  Author: Musta
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "TWI.h"

void EEPROM_WriteByte(u8 DeviceAdd, u8 LocAdd, u8 data);
u8 EEPROM_ReadByte(u8 DeviceAdd, u8 LocAdd);


#endif /* EEPROM_H_ */