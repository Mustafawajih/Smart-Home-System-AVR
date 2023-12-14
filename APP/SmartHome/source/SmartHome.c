/*
* SmartHome.c
*
* Created: 12/10/2023 4:36:39 PM
*  Author: Musta
*/

#include "SmartHome.h"
u8 Repeatpass=3;
u8 FlagAdmin=0;
u8 FlagUser=0;
u8 flagDisplayBluetooth=0;

//***********************************Keypad_Functions*******************
void SetPassword()
{
	// Read a byte from EEPROM at address 0b10100000 and offset 20, storing it in Pass_Set_Flag
	u8 Pass_Set_Flag = EEPROM_ReadByte(0b10100000, 20);

	// Check if the password is not set in EEPROM
	if (Pass_Set_Flag != 1)
	{
		// Variables to store user and admin passwords
		u8 Admin_Press_Password;
		u8 User_Press_Password;

		// Display welcome message on LCD
		LCD_Setpos(1, 3);
		LCD_String("Welcome To");
		LCD_Setpos(2, 3);
		LCD_String("Smart Home");
		_delay_ms(2000);

		// Clear the LCD screen
		LCD_Clear();
		LCD_Setpos(1, 0);
		LCD_String("Set Admin Pass:");
		LCD_Setpos(2, 0);

		////////////////////////////set Admin pass//////////////////////////
		// Loop to get each character of the admin password
		for (u8 i = 0; i < 4; i++) {
			Admin_Press_Password = GetKey();

			if (Admin_Press_Password != 0) {
				LCD_Char(Admin_Press_Password);
				AdminPassword[i] = Admin_Press_Password;
				_delay_ms(500);

				// Replace the entered character with '*'
				LCD_Setpos(2, i);
				LCD_Char('*');
			}
			else {
				i--; // No key pressed, retry for the same index
			}
		}
		AdminPassword[4] = '\0'; // Null terminator for the string

		// Store admin password in EEPROM
		for (u8 i = 0; i < 4; i++) {
			EEPROM_WriteByte(0b10100000, i, AdminPassword[i]);
			_delay_ms(200);
		}

		// Clear the LCD screen
		LCD_Clear();
		LCD_Setpos(1, 0);
		LCD_String("Set User Pass:");
		LCD_Setpos(2, 0);

		////////////////////////////set User pass//////////////////////////
		// Loop to get each character of the user password
		for (u8 i = 0; i < 4; i++) {
			User_Press_Password = GetKey();

			if (User_Press_Password != 0) {
				LCD_Char(User_Press_Password);
				UserPassword[i] = User_Press_Password;
				_delay_ms(500);

				// Replace the entered character with '*'
				LCD_Setpos(2, i);
				LCD_Char('*');
			}
			else {
				i--; // No key pressed, retry for the same index
			}
		}
		UserPassword[4] = '\0'; // Null terminator for the string

		// Store user password in EEPROM
		for (u8 i = 0; i < 4; i++) {
			EEPROM_WriteByte(0b10100000, i + 8, UserPassword[i]);
			_delay_ms(200);
		}

		// Clear the LCD screen
		LCD_Clear();
		LCD_Setpos(1, 0);
		LCD_String("All Pass Set");
		_delay_ms(500);

		// Set a flag in EEPROM to indicate that passwords are set
		EEPROM_WriteByte(0b10100000, 20, 1);
	}

}
//======================================================================
void login()
{
	// Declaration of variables
	u8 Mode = 0;
	u8 stored_upass[PASS_MAX_SIZE];
	u8 password;
	// Clear the LCD screen and display login options
	LCD_Clear();
	LCD_Setpos(1, 5);
	LCD_String("LOG-IN");
	LCD_Setpos(2, 0);
	LCD_String("1-Admin 2-User");
	// Wait for a valid choice (Admin or User)
	//  	do {
	//  		choice = GetKey();
	//  	} while (choice == STD_LOW);
	Mode = EnterKey();
	switch (Mode)
	{
		/**************************************  Admin Login *********************************************/
		case ADMIN_MODE:
		while(FlagAdmin!=ADMIN)
		{
			if (Repeatpass > 0)
			{
				// Prompt user to enter Admin password
				LCD_Clear();
				LCD_Setpos(1, 0);
				LCD_String("Enter Admin Pass");
				LCD_Setpos(2, 0);
				LCD_String("pass:");

				// Loop to get each character of the entered Admin password
				for (u8 i = 0; i < 4; i++)
				{
					password = GetKey();

					if (password != 0)
					{
						LCD_Char(password);
						AdminPassword[i] = password;
						_delay_ms(500);

						// Replace the entered character with '*'
						LCD_Setpos(2, i + 5);
						LCD_Char('*');
					}
					else
					{
						i--; // No key pressed, retry for the same index
					}
				}

				// Null terminator for the string
				AdminPassword[4] = '\0';

				// Read stored Admin password from EEPROM
				for (u8 i = 0; i < 4; i++)
				{
					stored_upass[i] = EEPROM_ReadByte(0b10100000, i);
				}

				// Check if entered Admin password matches stored password
				u8 count = 0;
				for (u8 i = 0; i < 4; i++)
				{
					if (stored_upass[i] == AdminPassword[i])
					{
						count++;
					}
				}
				// If the passwords match, grant access and perform actions
				if (count == PASS_MAX_SIZE)
				{
					FlagAdmin = 1;
					Repeatpass=0;
					LCD_Clear();
					LCD_String("success");
					LCD_Setpos(2, 0);
					LCD_String("Bluetooth ON");
					_delay_ms(500);
					Home_control_Bluetooth();
				}
				else
				{
					// Display failure message and decrement repeat count
					LCD_Clear();
					LCD_Setpos(1, 3);
					LCD_String("Wrong pass!");
					LCD_Setpos(2, 2);
					LCD_String("Tries left:");
					LCD_Char(Repeatpass-1+ZERO);
					_delay_ms(1000);
					Repeatpass--;

					// If no more repeats allowed, sound the buzzer
					if (Repeatpass == 0 && FlagAdmin == 0)
					{
						for (u8 i = 0; i < 30; i++)
						{
							Buzzer_void_ON();
							_delay_ms(100);
							Buzzer_void_OFF();
							_delay_ms(100);
						}
					}
				}
			}
			_delay_ms(200);
		}
		break;

		/**************************************  User Login*********************************************/
		case USER_MODE:
		while(FlagUser != USER)
		{
			if (Repeatpass > 0)
			{
				// Prompt user to enter User password
				LCD_Clear();
				LCD_Setpos(1, 0);
				LCD_String("Enter User Pass");
				LCD_Setpos(2, 0);
				LCD_String("pass:");

				// Loop to get each character of the entered User password
				for (u8 i = 0; i < 4; i++)
				{
					password = GetKey();

					if (password != 0)
					{
						LCD_Char(password);
						UserPassword[i] = password;
						_delay_ms(500);

						// Replace the entered character with '*'
						LCD_Setpos(2, i + 5);
						LCD_Char('*');
					}
					else
					{
						i--; // No key pressed, retry for the same index
					}
				}

				// Null terminator for the string
				UserPassword[4] = '\0';

				// Read stored User password from EEPROM
				for (u8 i = 0; i < 4; i++)
				{
					stored_upass[i] = EEPROM_ReadByte(0b10100000, i + 8);
				}

				// Check if entered User password matches stored password
				u8 count = 0;
				for (u8 i = 0; i < 4; i++)
				{
					if (stored_upass[i] == UserPassword[i])
					{
						count++;
					}
				}

				// If the passwords match, grant access and perform actions
				if (count == PASS_MAX_SIZE)
				{
					FlagUser = 1;
					Repeatpass=0;
					LCD_Clear();
					LCD_String("success");
					_delay_ms(500);
					displayBluetooth(5);
					Home_Control();
				}
				else
				{
					// Display failure message and decrement repeat count
					LCD_Clear();
					LCD_Setpos(1, 3);
					LCD_String("Wrong pass!");
					LCD_Setpos(2, 2);
					LCD_String("Tries left:");
					LCD_Char(Repeatpass-1+ZERO);
					_delay_ms(1000);
					Repeatpass--;
					// If no more repeats allowed, sound the buzzer
					if (Repeatpass == 0 && FlagUser == 0)
					{
						for (u8 i = 0; i < 30; i++)
						{
							Buzzer_void_ON();
							_delay_ms(100);
							Buzzer_void_OFF();
							_delay_ms(100);
						}
					}
				}
			}
			_delay_ms(500);
		}
		break;
		// If an invalid choice is made, go back to the login options
		default:
		break;
	}
}
//======================================================================
void Home_Control()
{
	u8 controlKey=0;
	LCD_Clear();
	LCD_Setpos(1, 1);
	LCD_String("Control system");
	_delay_ms(500);
	LCD_Clear();
	while(1)
	{
		LCD_Setpos(1, 0);
		LCD_String("1-Door  2-Rooms");
		LCD_Setpos(2, 3);
		LCD_String("3-Log-Out");
		controlKey = GetKey();
		if(controlKey != 0xff)
		{
			if(controlKey == DOOR )
			{DoorControl();}
			else if(controlKey == ROOMS )
			{RoomsControl();LCD_Clear();}
			else if(controlKey == LOG_OUT )
			{
				LCD_Clear();
				RESET();
				displayBluetooth(6);
				login();
			}
			else if (controlKey != NOT_PRESSED)
			{
				LCD_Clear();
				LCD_String("  Wrong input!");
				_delay_ms(500);
			}
		}
		
	}
}
//======================================================================
void RoomsControl()
{
	u8 RoomsKey=0;
	LCD_Clear();
	LCD_Setpos(1, 0);
	LCD_String("1-Room1 2-Room2");
	LCD_Setpos(2, 0);
	LCD_String("3-Room3 4-Room4");
	while(1)
	{
		RoomsKey = GetKey();
		if(RoomsKey != 0xff)
		{
			if(RoomsKey == ROOM1)
			{
				RoomsMenu(Room1);break;
			}
			else if(RoomsKey == ROOM2)
			{
				RoomsMenu(Room2);break;
			}
			else if(RoomsKey == ROOM3)
			{
				RoomsMenu(Room3);break;
			}
			else if(RoomsKey == ROOM4)
			{
				RoomsMenu(Room4);break;
			}
			else if (RoomsKey != NOT_PRESSED)
			{
				LCD_Clear();
				LCD_String("  Wrong input!");
				_delay_ms(500); break;
			}
			
		}
	}
}
//======================================================================
void RoomsMenu(u8 RoomNO)
{
	u8 RoomKey = 0;
	LCD_Clear();
	LCD_Setpos(1, 0);
	LCD_String("1-LED ON/OFF");
	LCD_Setpos(2, 0);
	LCD_String("2-Rooms ");
	_delay_ms(500);
	while(1)
	{
		RoomKey = GetKey();
		if(RoomKey != 0xff)
		{
			if(RoomNO == Room1)
			{	status_Led(Room1);
				if(RoomKey == LED_ON_OFF)
				{
					DIO_ToggleChannel(DIO_ChannelB0);
					displayBluetooth(1);
					break;
				}
				else if(RoomKey == ROOMS_BACK)
				{
					RoomsControl();
					break;
				}
			}
			else if(RoomNO == Room2)
			{
				status_Led(Room2);
				if(RoomKey == LED_ON_OFF)
				{
					DIO_ToggleChannel(DIO_ChannelD6);
					displayBluetooth(2);
					break;
				}
				else if(RoomKey == ROOMS_BACK)
				{
					RoomsControl();
					break;
				}
			}
			else if(RoomNO == Room3)
			{
				status_Led(Room3);
				if(RoomKey == LED_ON_OFF)
				{
					DIO_ToggleChannel(DIO_ChannelD7);
					displayBluetooth(3);
					break;
				}
				else if(RoomKey == ROOMS_BACK)
				{
					RoomsControl();
					break;
				}
			}
			else if(RoomNO == Room4)
			{
				status_Led(Room4);
				if(RoomKey == LED_ON_OFF)
				{
					DIO_ToggleChannel(DIO_ChannelB6);
					DIO_ToggleChannel(DIO_ChannelB7);
					displayBluetooth(4);
					break;
				}
				else if(RoomKey == ROOMS_BACK)
				{
					RoomsControl();
					break;
				}
			}

		}
	}
}
//======================================================================
void DoorControl()
{
	u8 DoorKey=0;
	LCD_Clear();
	LCD_String("Admin Only Access");
	LCD_Setpos(2, 0);
	LCD_String("Waiting...");
	_delay_ms(500);
	Bluetooth_TransmaitString("\r------------------------------");
	Bluetooth_TransmaitString("\rUser Requested To Open Door\r1-Open  2-Refuse\n");
	Bluetooth_TransmaitString("\r------------------------------");
	while(1)
	{
		DoorKey = Bluetooth_Receive();
		if(DoorKey != 0xff)
		{
			if(DoorKey == OPEN)
			{
				Bluetooth_TransmaitString("\rDoor Opened 5s");
				LCD_Clear();
				LCD_Setpos(1, 0);
				LCD_String("Door Opened 5s");
				Door();
				Bluetooth_TransmaitString("\rDoor Closed");
				break;
			}
			else if(DoorKey == REFUSE)
			{
				Bluetooth_TransmaitString("\rAdmin Denied");
				LCD_Clear();
				LCD_Setpos(1, 0);
				LCD_String("Admin Denied");
				_delay_ms(500);
				break;
			}
		}
		
	}
}
//======================================================================
void status_Led(u8 ledNo)
{
	// Check and display the status of Room1
	if(ledNo == Room1 )
	{
		u8 Room1_Read = DIO_ReadChannel(DIO_ChannelB0);
		if (Room1_Read == 1)
		{
			LCD_Setpos(2, 9);
			LCD_String("St:ON");
		}
		else
		{
			LCD_Setpos(2, 9);
			LCD_String("St:OFF");
		}
	}
	// Check and display the status of Room2
	else if(ledNo == Room2)
	{
		u8 Room2_Read = DIO_ReadChannel(DIO_ChannelD6);
		if (Room2_Read == 1)
		{
			//Bluetooth_TransmaitString("\rRoom2 LED ON");
			LCD_Setpos(2, 9);
			LCD_String("St:ON");
		}
		else
		{
			//	Bluetooth_TransmaitString("\rRoom2 LED OFF");
			LCD_Setpos(2, 9);
			LCD_String("St:OFF");
		}
	}
	else if(ledNo == Room3)
	{
		u8 Room3_Read = DIO_ReadChannel(DIO_ChannelD7);
		// Check and display the status of Room3
		if (Room3_Read == 1)
		{
			LCD_Setpos(2, 9);
			LCD_String("St:ON");
		}
		else
		{
			LCD_Setpos(2, 9);
			LCD_String("St:OFF");
		}
	}
	else if(ledNo == Room4)
	{
		u8 Room4_Read = DIO_ReadChannel(DIO_ChannelB6);
		if (Room4_Read == 1)
		{
			LCD_Setpos(2, 9);
			LCD_String("St:ON");
		}
		else
		{
			LCD_Setpos(2, 9);
			LCD_String("St:OFF");
		}
	}
	
}
//======================================================================
u8 EnterKey(void)
{
	u8 x;// Variable to store the pressed key
	do// Loop until a key is pressed (not in the low state)
	{
		x = GetKey();// Get the current key status
	} while (x == STD_LOW);  // Continue looping while the key is not pressed
	return x;// Return the pressed key
}
//****************************************Bluetooth_Functions***********
void Bluetooth_SetPass() {
	
	// Check if the EEPROM flag at address 30 is not set (value not equal to 1)
	if (EEPROM_ReadByte(0b10100000, 30) != 1)
	{
		// Send welcome messages to the Bluetooth module
		Bluetooth_TransmaitString("Welcome to smart home\n");
		Bluetooth_TransmaitString("\rset admin pass,please:\n");

		// Loop to receive and store the admin password in EEPROM
		for (u8 i = 0; i < PASS_MAX_SIZE; i++) {
			do {
				// Receive a character from Bluetooth and store it in AdminPassword
				AdminPassword[i] = Bluetooth_Receive();
			} while (AdminPassword[i] == 0);  // Continue looping while the received character is 0
			// Write the received character to EEPROM at the corresponding address
			EEPROM_WriteByte(0b10100000, i, AdminPassword[i]);
			_delay_ms(200);  // Delay for stability or acknowledgment
		}
		// Send a message indicating the successful setting of the admin password
		Bluetooth_TransmaitString("\rAdmin password set \n");
		Bluetooth_TransmaitString("\rset user pass \n");

		// Loop to receive and store the user password in EEPROM
		for (u8 i = 0; i < PASS_MAX_SIZE; i++) {
			do {
				// Receive a character from Bluetooth and store it in UserPassword
				UserPassword[i] = Bluetooth_Receive();
			} while (UserPassword[i] == 0);  // Continue looping while the received character is 0
			// Write the received character to EEPROM at the corresponding address
			EEPROM_WriteByte(0b10100000, i + 8, UserPassword[i]);
			_delay_ms(200);  // Delay for stability or acknowledgment
		}
		// Send a message indicating the successful setting of the user password

		Bluetooth_TransmaitString("\rUser password set\n");

		// Set the EEPROM flag at address 30 to 1, indicating that the setup is complete
		EEPROM_WriteByte(0b10100000, 30, 1);
	}

}
//======================================================================
void Bluetooth_Login()
{
	// Initialize a counter variable to keep track of successful password matches
	u8 count = 0;

	// Send a Bluetooth message indicating a login prompt
	Bluetooth_TransmaitString("\r LOG_IN\n");

	// Reset the counter variable to 0
	count = 0;
	while(FlagAdmin!=ADMIN)
	{
		Bluetooth_TransmaitString("\r Enter Your password:\n");// Send a Bluetooth message prompting the user to enter their password
		
		if (Repeatpass > 0)// Check if there are remaining login attempts (Repeatpass > 0)
		{
			
			for (u8 i = 0; i < PASS_MAX_SIZE; i++)// Loop to receive and validate each character of the entered password
			{
				do
				{
					AdminPassword[i] = Bluetooth_Receive();// Receive a character from Bluetooth and store it in AdminPassword
				} while (AdminPassword[i] == 0);  // Continue looping while the received character is 0

				adminLogin[i] = EEPROM_ReadByte(0b10100000, i);// Read the corresponding character from EEPROM for comparison

				if (adminLogin[i] == AdminPassword[i])// Check if the entered character matches the stored character in EEPROM
				{
					count++;  // Increment the counter for each successful character match
				}
			}

			// Check if the counter equals the length of the password (all characters matched)
			if (count == PASS_MAX_SIZE)
			{
				FlagAdmin=1;
				Repeatpass=0;
				// If all characters match, proceed to Bluetooth control
				Home_control_Bluetooth();
			}
			else
			{
				// If the password entry fails, decrement the repeat counter
				Repeatpass--;

				// Check if there are no more repeat attempts remaining
				if (Repeatpass == 0)
				{
					Bluetooth_TransmaitString("\r Failed!\n");
					// Activate a buzzer and toggle a specific channel (e.g., B0) in case of repeated failures
					for (u8 i = 0; i < 30; i++)
					{
						Buzzer_void_ON();
						_delay_ms(300);
						Buzzer_void_OFF();
						_delay_ms(300);
					}
					DIO_ToggleChannel(DIO_ChannelB0);
				}

				// Send a Bluetooth message indicating a failed login
				Bluetooth_TransmaitString("\r Failed!\n");

				// Repeat the login process (go back to the "again" label)
			}
		}
	}
}
//======================================================================
void Bluetooth_ChangePass()
{
	// Send Bluetooth messages to display password change options
	Bluetooth_TransmaitString("\r-------------------");
	Bluetooth_TransmaitString("\rChange Password");
	Bluetooth_TransmaitString("\r1-Admin Password\r2-User Password\r3-Back");

	// Receive the user's choice for password change from Bluetooth
	u8 Choice = Bluetooth_Receive();
	// Switch statement based on the user's password change choice
	switch (Choice)
	{
		case AdminPass_Change:
		// Send Bluetooth messages to prompt the user for a new Admin password
		Bluetooth_TransmaitString("\r-------------------");
		Bluetooth_TransmaitString("\rEnter New Password: ");
		// Loop to receive the new Admin password characters
		for (u8 i = 0; i < PASS_MAX_SIZE; i++)
		{
			// Wait for a valid character to be received
			do {
				AdminPassword[i] = Bluetooth_Receive();
			} while (AdminPassword[i] == 0);
			// Write the character to EEPROM
			EEPROM_WriteByte(0b10100000, i, AdminPassword[i]);
			// Delay for stability
			_delay_ms(200);
		}
		// Send Bluetooth message indicating Admin password set
		Bluetooth_TransmaitString("\rAdmin password set");
		break;

		case UserPass_Change:
		// Send Bluetooth messages to prompt the user for a new User password
		Bluetooth_TransmaitString("\r-------------------");
		Bluetooth_TransmaitString("\rEnter New Password: ");
		// Loop to receive the new User password characters
		for (u8 i = 0; i < PASS_MAX_SIZE; i++)
		{
			// Wait for a valid character to be received
			do {
				UserPassword[i] = Bluetooth_Receive();
			} while (UserPassword[i] == 0);
			// Write the character to EEPROM
			EEPROM_WriteByte(0b10100000, i+8, UserPassword[i]);
			// Delay for stability
			_delay_ms(200);
		}
		// Send Bluetooth message indicating User password set
		Bluetooth_TransmaitString("\rUser password set");
		break;

		case cancel_change:
		// Go back to the Bluetooth control functionality
		Home_control_Bluetooth();
		break;

		default:
		break;
	}

}
//======================================================================
void Home_control_Bluetooth()
{
	// Initialize a variable to store the user's ControlRec
	u8 ControlRec = 0;
	while(1)
	{
		Bluetooth_TransmaitString("\r-------------------------");
		Bluetooth_TransmaitString("\rControl system");
		Bluetooth_TransmaitString("\r0-Information");
		Bluetooth_TransmaitString("\r1-Door  \r2-Rooms");
		Bluetooth_TransmaitString("\r3-Log-Out");
		Bluetooth_TransmaitString("\r4-Change Password");
		Bluetooth_TransmaitString("\r-------------------------");
		u8 ControlRec = Bluetooth_Receive();// Receive the user's ControlRec from Bluetooth
		
		if(ControlRec == INFO)
		{LCD_Clear();Information();}
		else if(ControlRec == DOOR)
		{ DoorControl_Bluetooth();}
		else if(ControlRec == ROOMS)
		{RoomsControl_Bluetooth();}
		else if (ControlRec == LOG_OUT)
		{
			Bluetooth_TransmaitString("\r  LOGED_OUT ");
			// Clear LCD and reset system, then proceed to login
			LCD_Clear();
			RESET();
			login();
			break;
		}
		else if (ControlRec == ChangePass)
		{Bluetooth_ChangePass();}
	}
}
//======================================================================
void DoorControl_Bluetooth()
{
	u8 DoorRec=0;
	// Send Bluetooth messages to display door status and options
	Bluetooth_TransmaitString("\rStatus Closed");
	Bluetooth_TransmaitString("\r1-Open       ");
	Bluetooth_TransmaitString("\r-------------------------");
	
	while(1)
	{
		DoorRec = Bluetooth_Receive();
		if(DoorRec == DOOR_OPEEN)
		{
			Bluetooth_TransmaitString("\rDoor Opened 5s");
			Door();
			Bluetooth_TransmaitString("\rDoor Closed");
			break;
		}
	}
}
//======================================================================
void RoomsMenu_Bluetooth(u8 RoomNO)
{
	u8 RoomRec = 0;
	Bluetooth_TransmaitString("\r1-LED ON/OFF");
	Bluetooth_TransmaitString("\r2-Rooms ");
	Bluetooth_TransmaitString("\r-------------------------");
	while(1)
	{
		RoomRec = Bluetooth_Receive();
		if(RoomNO == Room1)
		{
			if(RoomRec == LED_ON_OFF)
			{
				DIO_ToggleChannel(DIO_ChannelB0);
				displayBluetooth(1);
				break;
			}
			else if(RoomRec == ROOMS_BACK)
			{
				RoomsControl_Bluetooth();
				break;
			}
		}
		else if(RoomNO == Room2)
		{
			if(RoomRec == LED_ON_OFF)
			{
				DIO_ToggleChannel(DIO_ChannelD6);
				displayBluetooth(2);
				break;
			}
			else if(RoomRec == ROOMS_BACK)
			{
				RoomsControl_Bluetooth();
				break;
			}
		}
		else if(RoomNO == Room3)
		{
			if(RoomRec == LED_ON_OFF)
			{
				DIO_ToggleChannel(DIO_ChannelD7);
				displayBluetooth(3);
				break;
			}
			else if(RoomRec == ROOMS_BACK)
			{
				RoomsControl_Bluetooth();
				break;
			}
		}
		else if(RoomNO == Room4)
		{
			if(RoomRec == LED_ON_OFF)
			{
				DIO_ToggleChannel(DIO_ChannelB6);
				DIO_ToggleChannel(DIO_ChannelB7);
				displayBluetooth(4);
				break;
			}
			else if(RoomRec == ROOMS_BACK)
			{
				RoomsControl_Bluetooth();
				break;
			}
		}
	}
}
//======================================================================
void RoomsControl_Bluetooth()
{
	u8 RoomsRec=0;
	Bluetooth_TransmaitString("\r1-Room1 2-Room2");
	Bluetooth_TransmaitString("\r3-Room3 4-Room4");
	Bluetooth_TransmaitString("\r-------------------------");
	while(1)
	{
		RoomsRec = Bluetooth_Receive();
		if(RoomsRec == ROOM1)
		{
			RoomsMenu_Bluetooth(Room1);
			break;
		}
		else if(RoomsRec == ROOM2)
		{
			RoomsMenu_Bluetooth(Room2);
			break;
		}
		else if(RoomsRec == ROOM3)
		{
			RoomsMenu_Bluetooth(Room3);
			break;
		}
		else if(RoomsRec == ROOM4)
		{
			RoomsMenu_Bluetooth(Room4);
			break;
		}
	}
}
//======================================================================
void displayBluetooth(u8 Message)
{
	// Read the status of various rooms
	u8 Room1_Read = DIO_ReadChannel(DIO_ChannelB0);
	u8 Room2_Read = DIO_ReadChannel(DIO_ChannelD6);
	u8 Room3_Read = DIO_ReadChannel(DIO_ChannelD7);
	u8 Room4_Read = DIO_ReadChannel(DIO_ChannelB6);
	u8 Room5_Read = DIO_ReadChannel(DIO_ChannelB7);

	// Check the value of the variable 'Message' to determine the action
	if (Message == 1)
	{
		// Display the current status of Room1 based on its read value
		Bluetooth_TransmaitString("\r--------------\n");
		if (Room1_Read == 1)
		{
			Bluetooth_TransmaitString("\r Led ON->>Room1");
		}
		else if (Room1_Read == 0)
		{
			Bluetooth_TransmaitString("\r Led off->>Room1");
			// Set a flag to indicate the display status for Bluetooth
			flagDisplayBluetooth = 0;
		}
	}
	else if (Message == 2)
	{
		// Display the current status of Room2 based on its read value
		Bluetooth_TransmaitString("\r--------------");
		if (Room2_Read == 1)
		{
			Bluetooth_TransmaitString("\r Led ON->>Room2");
		}
		else if (Room2_Read == 0)
		{
			Bluetooth_TransmaitString("\r Led off->>Room2");
		}
	}
	else if (Message == 3)
	{
		// Display the current status of Room3 based on its read value
		Bluetooth_TransmaitString("\r--------------");
		if (Room3_Read == 1)
		{
			Bluetooth_TransmaitString("\r Led ON->>Room3");
		}
		else if (Room3_Read == 0)
		{
			Bluetooth_TransmaitString("\r Led off->>Room3");
		}
	}
	else if (Message == 4)
	{
		// Display the current status of Room4 based on its read value
		Bluetooth_TransmaitString("\r--------------");
		if (Room4_Read == 1)
		{
			Bluetooth_TransmaitString("\r 2Led ON->>Room4");
		}
		else if (Room4_Read == 0)
		{
			Bluetooth_TransmaitString("\r 2Led off->>Room4");
		}
	}
	else if (Message == 5)
	{
		// Display a message indicating User LOG_IN
		Bluetooth_TransmaitString("\r User LOG_IN ");
		Bluetooth_TransmaitString("\r--------------");
	}
	else if (Message == 6)
	{
		// Display a message indicating User LOG_OUT
		Bluetooth_TransmaitString("\r--------------");
		Bluetooth_TransmaitString("\r User LOG_OUT");
		Bluetooth_TransmaitString("\r--------------");
	}
	else if (Message == 7)
	{
		// Display a message indicating User Requested To Open Door
		Bluetooth_TransmaitString("\r--------------");
		Bluetooth_TransmaitString("\r User Requested To Open Door ");
	}

}
//======================================================================
void Information()
{
	// Display system information
	LCD_Clear();
	LCD_Setpos(1, 0);
	LCD_String("Temp:");
	LCD_String(AdcString);
	
	// Read the status of various rooms
	u8 Room1_Read = DIO_ReadChannel(DIO_ChannelB0);
	u8 Room2_Read = DIO_ReadChannel(DIO_ChannelD6);
	u8 Room3_Read = DIO_ReadChannel(DIO_ChannelD7);
	u8 Room4_Read = DIO_ReadChannel(DIO_ChannelB6);
	// Check and display the status of Room1
	if (Room1_Read == 1)
	{
		Bluetooth_TransmaitString("\rRoom1 LED ON");
		LCD_Setpos(1, 9);
		LCD_String("R1-ON");
	}
	else
	{
		Bluetooth_TransmaitString("\rRoom1 LED OFF");
		LCD_Setpos(1, 9);
		LCD_String("R1-OFF");
	}
	
	// Check and display the status of Room2
	if (Room2_Read == 1)
	{
		Bluetooth_TransmaitString("\rRoom2 LED ON");
		LCD_Setpos(2, 0);
		LCD_String("R2-ON");
	}
	else
	{
		Bluetooth_TransmaitString("\rRoom2 LED OFF");
		LCD_Setpos(2, 0);
		LCD_String("R2-OFF");
	}
	
	// Check and display the status of Room3
	if (Room3_Read == 1)
	{
		Bluetooth_TransmaitString("\rRoom3 LED ON");
		LCD_Setpos(2, 7);
		LCD_String("R3-ON >0");
	}
	else
	{
		Bluetooth_TransmaitString("\rRoom3 LED OFF");
		LCD_Setpos(2, 7);
		LCD_String("R3-OFF >0");
	}
	
	Bluetooth_TransmaitString("\rMore>>0");
	// Receive user choice
	
	while(1)
	{
		u8 choice = Bluetooth_Receive();
		if(choice == MORE )
		{
			LCD_Clear();
			LCD_Setpos(1, 0);
			LCD_String("Temp:");
			LCD_String(AdcString);
			if (Room4_Read == 1)
			{
				Bluetooth_TransmaitString("\rRoom4 LED ON");
				LCD_Setpos(1, 8);
				LCD_String("R4-ON");
				LCD_Setpos(2, 0);
				LCD_String("Back>1");
			}
			else{
				Bluetooth_TransmaitString("\rRoom4 LED OFF");
				LCD_Setpos(1, 8);
				LCD_String("R4-OFF");
				LCD_Setpos(2, 0);
				LCD_String("Back>1");
			}
		}
		else if (choice == BACK_CONTROL)
		{
			Home_control_Bluetooth();
			break;
		}
	}
}
//======================================================================
void RESET()
{
	FlagAdmin = 0; // Reset the Admin flag
	FlagUser = 0;  // Reset the User flag
}
//======================================================================
void status_LedBluetooth(u8 ledNo)
{
	// Check and display the status of Room1
	if(ledNo == Room1 )
	{
		u8 Room1_Read = DIO_ReadChannel(DIO_ChannelB0);
		if (Room1_Read == 1)
		{
			Bluetooth_TransmaitString("\rStatus:ON");
		}
		else
		{
			Bluetooth_TransmaitString("\rStatus:OFF");
		}
	}
	// Check and display the status of Room2
	else if(ledNo == Room2)
	{
		u8 Room2_Read = DIO_ReadChannel(DIO_ChannelD6);
		if (Room2_Read == 1)
		{
			//Bluetooth_TransmaitString("\rRoom2 LED ON");
			Bluetooth_TransmaitString("\rStatus:ON");
		}
		else
		{
			//	Bluetooth_TransmaitString("\rRoom2 LED OFF");
			Bluetooth_TransmaitString("\rStatus:OFF");
		}
	}
	else if(ledNo == Room3)
	{
		u8 Room3_Read = DIO_ReadChannel(DIO_ChannelD7);
		// Check and display the status of Room3
		if (Room3_Read == 1)
		{
			Bluetooth_TransmaitString("\rStatus:ON");
		}
		else
		{
			Bluetooth_TransmaitString("\rStatus:OFF");
		}
	}
	else if(ledNo == Room4)
	{
		u8 Room4_Read = DIO_ReadChannel(DIO_ChannelB6);
		if (Room4_Read == 1)
		{
			Bluetooth_TransmaitString("\rStatus:ON");
		}
		else
		{
			Bluetooth_TransmaitString("\rStatus:OFF");
		}
	}
}