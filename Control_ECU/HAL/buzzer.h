 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer AVR driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "../std_types.h"


/*******************************************************************************
 *                      Static Configuration                                   *
 *******************************************************************************/

#define BUZZER_PortID PORTA_ID
#define BUZZER_PinID  PIN0_ID



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 	Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Input:
 * 	void
 * output:
 * 	void
 * */
void Buzzer_init();

/*
 * Description :
 * 	Function to disable the Buzzer through the GPIO.
 * Input:
 * 	void
 * output:
 * 	void
 * */
void Buzzer_off(void);


/*
 * Description :
 * 	Function to enable the Buzzer through the GPIO.
 * Input:
 * 	void
 * output:
 * 	void
 * */
void Buzzer_on(void);

#endif /* BUZZER_H_ */
