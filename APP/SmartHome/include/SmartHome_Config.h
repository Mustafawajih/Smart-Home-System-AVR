/*
 * SmartHome_Config.h
 *
 * Created: 12/10/2023 4:35:54 PM
 *  Author: Musta
 */ 


#ifndef SMARTHOME_CONFIG_H_
#define SMARTHOME_CONFIG_H_

// Maximum size for the password
#define PASS_MAX_SIZE		 4

#define ADMIN               '1'
#define USER                '1'
#define ZERO                '0'
// User modes
#define ADMIN_MODE			'1'
#define USER_MODE			'2'

// Commands for device control
#define INFO                '0'
#define DOOR				'1'
#define OPEN                '1'
#define REFUSE              '2'

#define ROOMS				'2'
#define LOG_OUT				'3'
#define ChangePass			'4'

// Additional commands for specific actions
#define MORE                '0'
#define BACK_CONTROL		'1'
#define AdminPass_Change	'1'
#define UserPass_Change		'2'
#define cancel_change		'3'

#define DOOR_OPEEN			'1'
#define BACK_MAIN			'2'

// Room identifiers
#define ROOM1				'1'
#define ROOM2				'2'
#define ROOM3				'3'
#define ROOM4				'4'
// control room
#define Room1                1
#define Room2                2
#define Room3                3
#define Room4                4
#define NOT_PRESSED          0

// Commands for controlling LED and rooms
#define LED_ON_OFF			'1'
#define ROOMS_BACK			'2'
#define BACK				'3'




#endif /* SMARTHOME_CONFIG_H_ */