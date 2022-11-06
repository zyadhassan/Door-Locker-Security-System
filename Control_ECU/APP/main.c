#include "../MCAL/gpio.h"
#include "util/delay.h"
#include "../MCAL/i2c.h"
#include "avr/io.h"
#include "../MCAL/uart.h"
#include "../MCAL/timer.h"
#include "../HAL/buzzer.h"
#include "../HAL/dcMotor.h"
#include "../HAL/external_eeprom.h"

#define Password_Address  0x00FF
#define TRUE_FLAG  'T'
#define FALSE_FLAG 'F'
#define ACK 0xFF


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 check_mathch_password(uint8 *password1, uint8 *password2);

void Option2_ChangePassword(void);

void Option1_OpenDoor(void);

void OpenDoor_MOTOR(void);

void ALARM_worongPassword(void);

void SET_Password(void);

uint8 Check_Password(void);

/********************************************************************************/


uint8 g_Timer_ticks = 0;


Timer1_ConfigType config_ptr = { 0, 8192,  Prescale_1024, CompareMode };/* 1 second = 8192*/


void countticks(void) {
	g_Timer_ticks++;
}



int main() {
	UART_ConfigType uart_config_ptr = { BIT_8, EVEN, One_bit, 9600 };
	UART_init(&uart_config_ptr);

	TWI_ConfigType twi_Config_Ptr = { 0x02, Fast };
	TWI_init(&twi_Config_Ptr);

	DcMotor_Init();
	Buzzer_init();
	Timer1_setCallBack(countticks);
	SREG |= (1 << 7);

	while (1) {
		uint8 recievedbyte = UART_recieveByte();
		switch(recievedbyte){
		case 'o':
			Option1_OpenDoor();
			break;
		case 'c':
			Option2_ChangePassword();
			break;
		case 's':
			SET_Password();
			break;
		case 'w':
			ALARM_worongPassword();
			break;
		default :
			break;
		}


	}
	return 0;
}



uint8 check_mathch_password(uint8 *password1, uint8 *password2) {
	for (uint8 i = 0; i < 5; i++) {
		if (password1[i] != password2[i]) {
			return FALSE_FLAG;
		}
	}
	return TRUE_FLAG;
}



void ALARM_worongPassword(void) {
	Buzzer_on();
	Timer1_init(&config_ptr);
	while (g_Timer_ticks < 60);
	g_Timer_ticks = 0;
	Buzzer_off();
	Timer1_deInit();
}



void OpenDoor_MOTOR() {
	DcMotor_Rotate(ON_C);
	Timer1_init(&config_ptr);
	while (g_Timer_ticks < 15);
	g_Timer_ticks = 0;
	DcMotor_Rotate(STOP);
	while (g_Timer_ticks < 3);
	g_Timer_ticks = 0;
	DcMotor_Rotate(ON_AC);
	while (g_Timer_ticks < 15);
	g_Timer_ticks = 0;
	DcMotor_Rotate(STOP);
	Timer1_deInit();
}


void SET_Password() {
	uint8 password1[6];
	uint8 password2[6];
	UART_receiveString(password1);
	UART_sendByte(ACK);
	UART_receiveString(password2);


	if(check_mathch_password(password1, password2)==TRUE_FLAG){

		for (uint8 i = 0; i < 5; i++) {
			EEPROM_writeByte(Password_Address + i, password1[i]);
			_delay_ms(20);
		}
		UART_sendByte(TRUE_FLAG);
	}
	else{
		UART_sendByte(FALSE_FLAG);
	}

}


uint8 Check_Password(void) {
	uint8 password[6];
	uint8 Savedpassword[6];
	UART_receiveString(password);
	for (uint8 i = 0; i < 5; i++) {
		EEPROM_readByte(Password_Address + i, &Savedpassword[i]);
		_delay_ms(20);
	}
	Savedpassword[5] = '\0';

	if(check_mathch_password(password, Savedpassword)==TRUE_FLAG){
		UART_sendByte(TRUE_FLAG);
		return TRUE_FLAG;
	}
	else{
		UART_sendByte(FALSE_FLAG);
		return FALSE_FLAG;
	}
}





void Option1_OpenDoor() {
	if(Check_Password()==TRUE_FLAG){
		OpenDoor_MOTOR();
	}
}
void Option2_ChangePassword() {
	if(Check_Password()==TRUE_FLAG){
		SET_Password();
	}
}




