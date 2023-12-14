/*
 * Dimmer.c
 *
 * Created: 12/10/2023 10:32:47 PM
 *  Author: Musta
 */ 

#include "Dimmer.h"

void initPWM() {
	
	// Set Timer 1 in Fast PWM mode, non-inverting mode
	TCCR1A |= (1 << COM1B1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	// Set prescaler to 8
	TCCR1B |= (1 << CS11);

	// Set OC1B (PD4) as output
	DDRD |= (1 << LED_PIN);

	// Set initial duty cycle to 0
	OCR1B = 0;
}

void setPWM(uint16_t dutyCycle) {
	// Set the duty cycle (0 to 65535) for OC1B
	OCR1B = dutyCycle;
}