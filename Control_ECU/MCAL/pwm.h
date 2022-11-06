 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the AVR PWM driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/


#ifndef PWM_H_
#define PWM_H_
#include "../std_types.h"

/*******************************************************************************
 *                                                                      *
 *******************************************************************************/
typedef enum{
	TIMER0=0,TIMER1A,TIMER1B,TIMER2
}Timer_Driver;

typedef enum{
	Non_Inverted=2,Inverted=3
}PWM_Mode;

typedef enum {
	OFF=0,Divide_1,Divide_8,Divide_64,Divide_256,Divide_1024
}Prescaler;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup The PWM Driver by passing which timer in avr
 *
 */
void init_PWM(Timer_Driver t , PWM_Mode p ,Prescaler scale);

/*
 * Description :
 * Start Generation of PWM signal
 *
 * INPUT:
 * the Duty Cycle of the output PWM Signal
 *
 *
 * */

void PWM_Timer0_Start(uint8 DutyCycle);
#endif /* PWM_H_ */
