/*
 * Smart Home Control System
 * Project Idea:
 * Remotely controlled system using a mobile or laptop for regular operation,
 * and a backup user mode with an LCD and keypad for emergency or alternative control.
 *
 * The controllable devices include 5 on/off lamps, one dimming lamp, a door,
 * and an air conditioner based on ambient temperature.
 *
 * The system features a login system with admin and user modes. The admin mode
 * allows registration and removal of users. Usernames and passwords persist in memory
 * even after a power cycle.
 *
 * If there are more than 3 incorrect login attempts by admin, user, or password,
 * the system goes into a breakdown state with a fire alarm until reset.
 *
 * Admin and user have access to all devices, except the user cannot control door opening.
 *
 * Main Function:
 * Initializes the system components, sets the password, and performs the login process.
 * Additional functions, such as PWM initialization and duty cycle changes, are commented out.
 * The program relies on an Interrupt Service Routine (ISR) to handle periodic tasks.
 */
//-------------------------------------------------------------------------------
/* Include Header Files From LIB */
#include "Clock.h"          // Clock-related functions or configurations
/* Include Header Files From MCAL Layer */
#include "DIO.h"            // Digital Input/Output functions
#include "TWI.h"            // Two-Wire Interface (I2C) functions
#include "UART.h"           // Universal Asynchronous Receiver-Transmitter functions
#include "ADC.h"            // Analog-to-Digital Converter functions
#include "Timer1.h"         // Timer1 functions
#include "Timer0.h"         // Timer0 functions
#include "EXT_int.h"        // External Interrupt functions
#include "GNIT.h"           // Generic Interrupt functions
//---------------------------------------------------------------------------
/* Include Header Files From HAL Layer */
#include "LCD.h"            // LCD (Liquid Crystal Display) functions
#include "LM35.h"           // LM35 temperature sensor functions
#include "Motor.h"          // Motor control functions
#include "Bluetooth.h"      // Bluetooth communication functions
#include "keypad.h"         // Keypad input functions
#include "EEPROM.h"         // EEPROM (Electrically Erasable Programmable Read-Only Memory) functions
#include "Buzzer.h"         // Buzzer-related functions
#include "ServoMotor.h"     // Servo motor control functions
#include "Dimmer.h"         //Dimmer Led 
/* Include Header Files From APP */
#include "SmartHome.h"      // Smart Home project-specific functions

// Global Variables 
u8 count=0;
u16 AdcRead=0;
s8 AdcString[10];
//-----------------------------------------------------------------------------
// Function to initialize the system components
void SystemInit()
{
// Initialize the LCD module
LCD_Init();

// Initialize the keypad for input
Keypad_Init();

// Initialize the buzzer for audio signals
Buzzer_void_init();

// Initialize the motor system
MotorInit();

// Initialize the Two-Wire Interface (I2C) with a specific address
TWI_Init(0b00001111);

// Configure and initialize the Analog-to-Digital Converter with specified options
ADC_InitTypes option = {ADC_Vref_Internal, ADC_Prescale128};
LM35_Init(&option);

// Configure and initialize the Bluetooth communication with specified options
UART_ConfigTypes options1 = {BaudRate_9600, DoubleSpeed_Disable, CharacterSize_8, Stop_1Bit, Parity_Disable, TX_Enable, RX_Enable};
Bluetooth_Init(&options1);

// Configure digital output channels for LEDs
DIO_ConfigChannel(DIO_ChannelB0, DIO_OUTPUT); // led1
DIO_ConfigChannel(DIO_ChannelD6, DIO_OUTPUT); // led2
DIO_ConfigChannel(DIO_ChannelD7, DIO_OUTPUT); // led3
DIO_ConfigChannel(DIO_ChannelB6, DIO_OUTPUT); // led4
DIO_ConfigChannel(DIO_ChannelB7, DIO_OUTPUT); // led5


// Configure a digital input channel for the LM35 temperature sensor
DIO_ConfigChannel(DIO_ChannelA1, DIO_INPUT); // ADC-->LM35

// Set the initial position of the servo motor to 180 degrees
ServoMotor(180);

// Initialize Timer0 in CTC (Clear Timer on Compare Match) mode
timer0_initializeCTC();
}

//------------------------------------------------------------------------------
int main()
{	
	// Initialize the system components
	SystemInit();
	// Set the password for admin and user
	SetPassword();
	// Perform the login process for admin and user
	while(1)
	{
		login();	
	}
	
}
//---------------------------------------------------------------------------
// Function to open and close the door using a servo motor
void Door()
{
	ServoMotor(0);
	_delay_ms(1000);
	ServoMotor(180);
}
//------------------------------------------------------------------------------
// Interrupt Service Routine for TIMER0 Compare Match
 ISR(TIMER0_COMP_vect)
 {
 // Increment the count variable
 count++;
 
 // Check if count reaches a threshold of 10
 if (count >= 10)
 {
 	// Reset the count to 0
 	count = 0;
 
 	// Read the value from the LM35 temperature sensor on ADC channel 1
 	AdcRead = LM35_Read(ADC_Channel1);
 
 	// Convert the ADC reading to a string
 	itoa(AdcRead, AdcString, 10);
 
 	// Check if the temperature reading is greater than 28 degrees
 	if (AdcRead > 28)
 	{
 		// Turn the motor ON
 		Motor_ON();
 	}
 	// If the temperature reading is less than 21 degrees
 	else if (AdcRead < 21)
 	{
 		// Turn the motor OFF
 		Motor_OFF();
 	}
 }
 }
//------------------------------------------------------------------------------