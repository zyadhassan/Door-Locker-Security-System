 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C AVR driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "../std_types.h"
/*******************************************************************************
 *                            Configurations                                   *
 *******************************************************************************/
typedef enum{
	Normal=100000U,Fast=400000U,FastPlus=1000000U,HighSpeed=3400000U
}TWI_BaudRate;

typedef uint8 TWI_Address;


typedef struct{
	TWI_Address address;
	TWI_BaudRate bit_rate;
}TWI_ConfigType;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * 	Initialize the TWI Driver based on Configuration
 * Input:
 * 	pointer to structure TWI_ConfigType
 * output:
 * 	0 for Error
 * 	1 For Success
 * */
uint8 TWI_init(const TWI_ConfigType * Config_Ptr);


/*
 * Description :
 * 	Starting the Frame
 * Input:
 * 	void
 * output:
 * 	void
 * */
void TWI_start(void);


/*
 * Description :
 * 	Stoping the Frame
 * Input:
 * 	void
 * output:
 * 	void
 * */
void TWI_stop(void);

/*
 * Description :
 * 	Write Byte on SDA
 * Input:
 * 	Byte to send
 * output:
 * 	void
 * */
void TWI_writeByte(uint8 data);

/*
 * Description :
 * 	Reading Byte with ACK
 * Input:
 * 	void
 * output:
 * 	Byte to read
 * */
uint8 TWI_readByteWithACK(void);

/*
 * Description :
 * 	Reading Byte without ACK
 * Input:
 * 	void
 * output:
 * 	Byte to read
 * */
uint8 TWI_readByteWithNACK(void);

/*
 * Description :
 * 	Know the status of the TWI
 * Input:
 * 	void
 * output:
 * 	Status
 * */
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */

