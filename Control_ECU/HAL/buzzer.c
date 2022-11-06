 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source  file for the buzzer AVR driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/
#include "../common_macros.h"
#include "avr/io.h"
#include "../MCAL/gpio.h"
#include "buzzer.h"

void Buzzer_init(){
	 GPIO_setupPinDirection(BUZZER_PortID,BUZZER_PinID,PIN_OUTPUT);
	 GPIO_writePin(BUZZER_PortID,BUZZER_PinID,LOGIC_LOW);
}


void Buzzer_off(void){
	GPIO_writePin(BUZZER_PortID,BUZZER_PinID,LOGIC_LOW);
}

void Buzzer_on(void){
	GPIO_writePin(BUZZER_PortID,BUZZER_PinID,LOGIC_HIGH);

}
