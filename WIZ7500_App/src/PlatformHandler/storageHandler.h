/*
 * storageHandler.h
 *
 *  Created on: 2014. 9. 16.
 *      Author: Raphael Kwon
 */

#ifndef STORAGEHANDLER_H_
#define STORAGEHANDLER_H_

#include <stdint.h>
#include "W7500x_i2c.h"

#define EEPROM_BLOCK_SIZE       	256
#define EEPROM_BLOCK_COUNT       	4
#define EEPROM_PAGE_SIZE       		16

int read_storage(uint8_t isConfig, void *data, uint16_t size);
int write_storage(uint8_t isConfig, void *data, uint16_t size);

int I2C1_Write(uint8_t block, uint8_t addr, uint8_t* data, uint8_t len);
int I2C1_Read(uint8_t block, uint8_t addr, uint8_t* data, uint32_t len);

extern I2C_ConfigStruct conf;
extern void delay(__IO uint32_t milliseconds);

#endif /* STORAGEHANDLER_H_ */
