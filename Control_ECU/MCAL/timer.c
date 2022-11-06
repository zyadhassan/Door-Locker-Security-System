 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER1 AVR driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/
#include "../common_macros.h"
#include "avr/io.h"
#include "timer.h"
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)();
		}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)();
		}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A=(1<<FOC1A);
	TCNT1=Config_Ptr->initial_value;
	SREG|=(1<<7);

	if(Config_Ptr->mode == NormalMode){
		TCCR1B=0x00;
		TIMSK|=(1<<TOIE1);
	}
	else if(Config_Ptr->mode == CompareMode){
		TCCR1B =(1<<WGM12);
		TIMSK|=(1<<OCIE1A);
		OCR1A=Config_Ptr->compare_value;

	}

	TCCR1B=(TCCR1B&0xF8) | ((Config_Ptr->prescaler)&0x07);
}


void Timer1_deInit(void){
	TCCR1B=0;
	TCCR1A=0;
}


void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}





