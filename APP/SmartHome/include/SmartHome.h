/*
 * SmartHome.h
 *
 * Created: 12/10/2023 4:36:24 PM
 *  Author: Musta
 */ 

#ifndef SMARTHOME_H_
#define SMARTHOME_H_

#include "SmartHome_Config.h"
#include "Clock.h"
#include "STD.h"
#include "DIO.h"

u8 AdminPassword[PASS_MAX_SIZE]; // 4 digit password
u8 UserPassword [PASS_MAX_SIZE]; // 4 digit password
u8 adminLogin   [PASS_MAX_SIZE]; // 4-digit password
u8 userLogin    [PASS_MAX_SIZE]; // 4-digit password
s8 AdcString[10];

//******************************Prototype***************************//
void SetPassword();// Function to set the password for admin and user
void login();// Function to handle the login process for admin and user
void Home_Control();// Function to control various devices in the system
void RoomsControl();
void RoomsMenu(u8 RoomNO);
void DoorControl();
void status_Led(u8 ledNo);
void Bluetooth_SetPass();// Function to set the password using Bluetooth communication
void Bluetooth_Login();// Function to handle the login process using Bluetooth
void Home_control_Bluetooth();// Function to control devices using Bluetooth communication
void Bluetooth_ChangePass();// Function to change the password using Bluetooth communication
void RoomsControl_Bluetooth();
void RoomsMenu_Bluetooth(u8 RoomNO);
void RoomsMenu_Bluetooth(u8 RoomNO);
void displayBluetooth(u8 Message);// Function to display messages through Bluetooth communication
void Information();// Function to display information about the system
void status_LedBluetooth(u8 ledNo);
void RESET();// Function to reset the system
u8   EnterKey(void);// Function to read and return a key entered by the user
//*********************************************************************//
#endif /* SMARTHOME_H_ */