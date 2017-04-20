/*
 * storageHandler.c
 *
 *  Created on: 2014. 9. 16.
 *      Author: Raphael Kwon
 */


#include <string.h>
#include "W7500x.h"
#include "storageHandler.h"
#include "flashHandler.h"

int read_storage(uint8_t isConfig, void *data, uint16_t size)
{
#if !defined(__USE_EXT_EEPROM__)
	uint32_t address;

	if(isConfig == 1) {
#if !defined(MULTIFLASH_ENABLE)
		address = (FLASH_PAGE_SIZE*2) + CONFIG_PAGE_ADDR;
#else
		address = flash.flash_page_size + flash.config_page_addr;
#endif
	}
	else {
#if !defined(MULTIFLASH_ENABLE)
		address = 0x00000000 + CONFIG_PAGE_ADDR;
#else
		address = 0x00000000 + flash.config_page_addr;
#endif
	}

	return read_flash(address, data, size);
#else
	int ret=0, i;
	uint8_t Receive_Data[EEPROM_BLOCK_SIZE];

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	memset(&Receive_Data[0], 0x00, EEPROM_BLOCK_SIZE);

    for(i=0; i<size; i++)
    {
    	ret = I2C1_Read(isConfig, i, &Receive_Data[i], 1);
    }
    //ret = I2C1_Read(isConfig, 0x00, &Receive_Data[0], size);

	memcpy(data, &Receive_Data[0], size);

#if 0
    printf("[DB R] %d\r\n", isConfig);
	for(i=0; i<249; i++)
		printf("0x%.2X ",Receive_Data[i]);
	printf("\r\n");
#endif

	return ret;
#endif
}

int write_storage(uint8_t isConfig, void *data, uint16_t size)
{
#if !defined(__USE_EXT_EEPROM__)
	uint32_t address;
	int ret;

	if(isConfig == 1) {
#if !defined(MULTIFLASH_ENABLE)
		address = (FLASH_PAGE_SIZE*2) + CONFIG_PAGE_ADDR;
#else
		address = flash.flash_page_size + flash.config_page_addr;
#endif
	}
	else {
#if !defined(MULTIFLASH_ENABLE)
		address = 0x00000000 + CONFIG_PAGE_ADDR;
#else
		address = 0x00000000 + flash.config_page_addr;
#endif
	}

	erase_flash_page(address);
	erase_flash_page(address+FLASH_PAGE_SIZE);

	ret = write_flash(address, data, size);
#else
	int ret=0;
	uint8_t page, rest, i, addr;
	uint8_t Transmit_Data[EEPROM_BLOCK_SIZE];

	memset(&Transmit_Data[0], 0x00, EEPROM_BLOCK_SIZE);
	memcpy(&Transmit_Data[0], data, size);

	if(size > EEPROM_BLOCK_SIZE)
		size = EEPROM_BLOCK_SIZE;

	page = size/EEPROM_PAGE_SIZE;
	rest = size%EEPROM_PAGE_SIZE;

	addr = 0;

	if(size < EEPROM_PAGE_SIZE)
	{
		ret = I2C1_Write(isConfig, addr, &Transmit_Data[0], size);
		delay(5);
	}
	else
	{
		for(i=0; i<page; i++)
		{
			addr = i*EEPROM_PAGE_SIZE;
			ret = I2C1_Write(isConfig, addr, &Transmit_Data[addr], EEPROM_PAGE_SIZE);
			delay(5);
		}

		if(rest != 0)
		{
			addr = page*EEPROM_PAGE_SIZE;
			ret = I2C1_Write(isConfig, addr, &Transmit_Data[addr], rest);
			delay(5);
		}
	}
#endif

	return ret;
}

int I2C1_Write(uint8_t block, uint8_t addr, uint8_t* data, uint8_t len)
{
	uint32_t i;
	uint8_t bsb;

	bsb = block<<1;

	if(len>EEPROM_PAGE_SIZE)
		len = EEPROM_PAGE_SIZE;

	I2C1_Start();

	//Write control
    I2C1_WriteByte(0xA0+bsb);
    I2C1_Wait_Ack();

    //Write address
    I2C1_WriteByte(addr);
    I2C1_Wait_Ack();

    //Write data
	for(i=0; i<len; i++)
	{
		I2C1_WriteByte(data[i]);
		I2C1_Wait_Ack();
	}

    I2C1_Stop();

    return 0;//success
}

int I2C1_Read(uint8_t block, uint8_t addr, uint8_t* data, uint32_t len)
{
	uint32_t i;
	uint8_t bsb;

	bsb = block<<1;

	I2C1_Start();

	//Write control
	I2C1_WriteByte(0xA0+bsb);
    I2C1_Wait_Ack();

    //Write address
    I2C1_WriteByte(addr);
    I2C1_Wait_Ack();

    I2C1_Start();

    //Write control
    I2C1_WriteByte(0xA1+bsb);
    I2C1_Wait_Ack();

    //Read data
    for(i=0; i<len; i++)
    {
    	if(i == (len-1))
    		data[i] = I2C1_ReadByte(0);
    	else
    		data[i] = I2C1_ReadByte(1);
    }

    I2C1_Stop();

    return 0;//success
}
