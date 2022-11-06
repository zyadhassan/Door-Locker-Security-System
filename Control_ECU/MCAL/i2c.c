 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C AVR driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/

#include "../common_macros.h"
#include "avr/io.h"
#include "i2c.h"


uint8 TWI_init(const TWI_ConfigType * Config_Ptr){
	float32 clk =((float32)F_CPU/Config_Ptr->bit_rate);
	if((clk-16)<=0){
		return 0;
	}
	else{
		clk=clk-16;
		clk=(float32)clk/2;
		if((float32)clk/(4) < 1){
			TWSR = 0x00;
			clk=clk/1;
		}
		else{
			if((float32)clk/(16) < 1){
				TWSR = 0x01;
				clk=clk/4;

			}
			else{
				if((float32)clk/(64) < 1){
					TWSR = 0x02;
					clk=clk/16;

				}
				else{
					TWSR = 0x03;
					clk=clk/64;

				}
			}
		}

	}
	TWBR=(uint8)clk;


    TWAR = (Config_Ptr->address)<<1;
    TWAR |= 1;

    TWCR = (1<<TWEN);
    return 1;
}

void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

