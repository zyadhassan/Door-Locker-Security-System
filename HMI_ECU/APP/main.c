#include "../MCAL/gpio.h"
#include "util/delay.h"
#include "avr/io.h"
#include "../MCAL/uart.h"
#include "../MCAL/timer.h"
#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
#include "../std_types.h"

#define TRUE_FLAG  'T'
#define FALSE_FLAG 'F'

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void GET_Password(uint8 *arr);

void Option2_ChangePassword(void);

void Option1_OpenDoor(void);

void OpenDoor_MOTOR(void);

void ALARM_worongPassword(void);

void SET_Password(void);


/********************************************************************************/

uint8 g_Timer_ticks = 0;

Timer1_ConfigType config_ptr = { 0, 8192, Prescale_1024, CompareMode };	/* 1 second = 8192*/


void countticks(void) {
	g_Timer_ticks++;
}


int main() {

	UART_ConfigType uart_config_ptr = { BIT_8, EVEN, One_bit, 9600 };
	UART_init(&uart_config_ptr);

	LCD_init();
	Timer1_setCallBack(countticks);
	SREG |= (1 << 7);

	SET_Password();

	while (1) {
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("- : Change Pass");

		uint8 choice = KEYPAD_getPressedKey();
		_delay_ms(200);
		if (choice == '+') {
			Option1_OpenDoor();


		} else if (choice == '-') {
			Option2_ChangePassword();
		}
	}
	return 0;
}

void SET_Password(void) {
	LCD_clearScreen();
	uint8 password1[6];
	uint8 password2[6];
	do {
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Plz enter pass:");
		LCD_moveCursor(1, 0);
		GET_Password(password1);
		LCD_moveCursor(0, 0);
		LCD_clearScreen();
		LCD_displayString("Plz re-enter the");
		LCD_moveCursor(1, 0);
		LCD_displayString("same pass:");
		GET_Password(password2);
		UART_sendByte('s');
		UART_sendString(password1);
		UART_sendByte('#');
		UART_recieveByte();
		UART_sendString(password2);
		UART_sendByte('#');

	} while (UART_recieveByte() != 'T');

}

void ALARM_worongPassword(){
	UART_sendByte('w');
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("****Error!****");
	Timer1_init(&config_ptr);
	while (g_Timer_ticks < 60);
	g_Timer_ticks = 0;
	LCD_clearScreen();
	Timer1_deInit();
}
void OpenDoor_MOTOR(){
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Door is Unlocking");
	Timer1_init(&config_ptr);
	while (g_Timer_ticks < 15)
		;
	g_Timer_ticks = 0;
	LCD_clearScreen();
	while (g_Timer_ticks < 3)
		;
	g_Timer_ticks = 0;
	LCD_displayString("Door is locking");
	while (g_Timer_ticks < 15)
		;
	g_Timer_ticks = 0;
	Timer1_deInit();
}





void Option1_OpenDoor(){
	uint8 pass[6];
	uint8 ans;
	uint8 WrongTrails=0;
	do{
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Plz enter pass:");
		LCD_moveCursor(1, 0);
		GET_Password(pass);

		UART_sendByte('o');
		UART_sendString(pass);
		UART_sendByte('#');
		ans = UART_recieveByte();
		if(ans==FALSE_FLAG)WrongTrails++;
	}while((ans==FALSE_FLAG) && (WrongTrails<3));

	if (ans == TRUE_FLAG) {
		OpenDoor_MOTOR();
	} else {
		ALARM_worongPassword();
	}
}
void Option2_ChangePassword(){
	uint8 pass[6];
	uint8 WrongTrails=0;
	uint8 ans;
	do{
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Plz enter pass:");
		LCD_moveCursor(1, 0);
		GET_Password(pass);
		UART_sendByte('c');
		UART_sendString(pass);
		UART_sendByte('#');

		ans = UART_recieveByte();
		if(ans==FALSE_FLAG)WrongTrails++;
	}while((ans==FALSE_FLAG) && (WrongTrails<3));


	if (ans == TRUE_FLAG) {
		SET_Password();
	} else {
		ALARM_worongPassword();
	}
}

void GET_Password(uint8 *arr) {
	uint8 i = 0;
	for (; i < 5;) {
		arr[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(200);
	}
	arr[i] = '\0';
	uint8 eq = ' ';
	while (eq != '=') {
		eq = KEYPAD_getPressedKey();
		_delay_ms(200);
	}

}


