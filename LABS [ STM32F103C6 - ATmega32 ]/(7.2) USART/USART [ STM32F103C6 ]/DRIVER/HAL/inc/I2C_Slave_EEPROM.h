/*
 * I2C_Slave_EEPROM.h
 *
 *  ENG.TERA
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

#include "I2C_DRIVER.h"


#define EEPROM_Slave_Address  	0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes,uint8_t Data_Lenght);
unsigned char eeprom_read_byte(unsigned int address, uint8_t* dataOut,uint8_t dataLen);



#endif /* INC_I2C_SLAVE_EEPROM_H_ */
