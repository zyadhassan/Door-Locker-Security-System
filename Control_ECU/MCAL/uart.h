 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author:Zyad Hassan
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../std_types.h"
/*******************************************************************************
 *                            Configurations                                   *
 *******************************************************************************/
typedef enum{
	bit_8=3,bit_7=2,bit_6=1,bit_5=0,bit_9=7
}UART_BitData;


typedef enum{
	Disable=0,ODD=3,EVEN=2
}UART_Parity;



typedef enum{
	One_Stopbit=0,Two_Stopbit=1
}UART_StopBit;




typedef uint32 UART_BaudRate;



typedef struct{
UART_BitData bit_data;
UART_Parity parity;
UART_StopBit stop_bit;
UART_BaudRate baud_rate;
}UART_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 *
 * Input :
 * 	 Pointer to Structure of UART_ConfigType which contains all Configurations
 */
void UART_init(const UART_ConfigType * Config_Ptr);


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
