 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcMotor.c
 *
 * Description: Source file for the LM35 DC Motor driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/


#include "dcMotor.h"
#include "../MCAL/gpio.h"
#include "../MCAL/pwm.h"



void DcMotor_Init(void){
	GPIO_setupPinDirection(DC_MOTOR_PORTID,DC_MOTOR_PIN1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORTID,DC_MOTOR_PIN2,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORTID,DC_MOTOR_ENB,PIN_OUTPUT);
	init_PWM(TIMER0,Non_Inverted,Divide_8);
	GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN1,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN2,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state){
	switch(state){
	case 0  :
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN2,LOGIC_LOW);
		init_PWM(TIMER0,Non_Inverted,OFF);

		break;
	case 1 :
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN1,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN2,LOGIC_LOW);
		init_PWM(TIMER0,Non_Inverted,Divide_8);
		PWM_Timer0_Start(255);
		break;
	case 2:
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORTID,DC_MOTOR_PIN2,LOGIC_HIGH);
		init_PWM(TIMER0,Non_Inverted,Divide_8);
		PWM_Timer0_Start(255);


	}
}

