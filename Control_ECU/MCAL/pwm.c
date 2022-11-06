/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the AVR PWM driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/

#include "pwm.h"
#include "../common_macros.h"
#include <avr/io.h>
#include "./gpio.h"





void init_PWM(Timer_Driver t , PWM_Mode p , Prescaler scale){

	switch (t){
	case 0:
		/* intilize timer by 0 */
		TCNT0=0;
		/*  Setupt The pin to be output */
		GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
		/*   Setup The Timer to be Fast PWM , Mode , Prescaling */
		TCCR0=(1<<WGM00) | (1<<WGM01) | ((p&0x03)<<COM00) | (scale&0x07);

		break;
	case 1:
		GPIO_setupPinDirection(PORTD_ID,PIN4_ID,PIN_OUTPUT);
		break;
	case 2:
		GPIO_setupPinDirection(PORTD_ID,PIN5_ID,PIN_OUTPUT);
		break;
	case 3:
		GPIO_setupPinDirection(PORTD_ID,PIN7_ID,PIN_OUTPUT);
		break;
	}
}

void PWM_Timer0_Start(uint8 DutyCycle){
	OCR0  = DutyCycle;

}

