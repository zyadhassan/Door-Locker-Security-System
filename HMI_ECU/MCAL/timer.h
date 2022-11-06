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

#ifndef TIMER_H_
#define TIMER_H_

#include "../std_types.h"
/*******************************************************************************
 *                            Configurations                                   *
 *******************************************************************************/

typedef enum {
	Prescale_1=1,Prescale_8=2,Prescale_64=3,Prescale_256=4,Prescale_1024=5
}Timer1_Prescaler;

typedef enum{
	NormalMode,CompareMode
}Timer1_Mode;


typedef struct {
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 	Function to initialize the Timer driver
 * Input:
 * 	pointer to the configuration structure with type Timer1_ConfigType
 * output:
 * 	void
 * */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);


/*
 * Description :
 * 	Function to disable the Timer1.
 * Input:
 * 	void
 * output:
 * void
 * */
void Timer1_deInit(void);


/*
 * Description :
 * 	Function to set the Call Back function address.
 * Input:
 * 	pointer to Call Back function.
 * output:
 * 	void
 * */
void Timer1_setCallBack(void(*a_ptr)(void));























#endif
