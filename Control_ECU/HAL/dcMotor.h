 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcMotor.h
 *
 * Description: Header file for the LM35 DC Motor driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "../std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORTID  PORTB_ID
#define DC_MOTOR_PIN1    PIN1_ID
#define DC_MOTOR_PIN2    PIN0_ID
#define DC_MOTOR_ENB     PIN3_ID


/*******************************************************************************
 *                               Types Declaration                                    *
 *******************************************************************************/
typedef enum{
	STOP=0,ON_C,ON_AC
}DcMotor_State;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * 1) The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * 2) Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_Init(void);


/*
 *
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 * Inputs:
 *  state: The required DC Motor state, it should be CW or A-CW or stop.
 *  speed: decimal value for the required motor speed, it should be from 0 → 100. For example, if the input is 50, The motor should rotate with 50% of its maximum speed.
 * */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DCMOTOR_H_ */
