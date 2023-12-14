/*
 * Timer0.h
 *
 * Created: 12/8/2023 10:02:51 PM
 *  Author: Musta
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "BIT_MATH.h"
#include "STD.h"
#include "DIO.h"

/*
	Function Name        : timer0_initializeCTC
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize and start the timer0 for compare match.
*/
void timer0_initializeCTC(void);

/*
	Function Name        : timer0_stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : Stop timer0.
*/
void timer0_stop(void);

/*
	Function Name        : timer_initializefastpwm
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer0 for FastPWM mode.
*/
void timer_initializefastpwm(void);

/*
	Function Name        : LCD_vInit
	Function Returns     : void
	Function Arguments   : float64 duty
	Function Description : Set duty cycle to the given duty percentage.
*/
void change_dutycycle(f64 duty);

#endif /* TIMER0_H_ */