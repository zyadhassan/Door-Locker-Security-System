#include "../MCAL/gpio.h"
#include "util/delay.h"
#include "../MCAL/i2c.h"





int main(){
	TWI_ConfigType config_i2c ={Fast,0x01};
	TWI_init(&config_i2c);







}
