/*
  NfcTag.h
  
  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author: lawliet zou
  Email: lawliet.zou@gmail.com
  Data: 2014-03-25
  Version: 0.1

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "arduino.h"
#include <Wire.h>

#ifndef __NFC_TAG_H__
#define __NFC_TAG_H__


#define EEPROM_ADDR_E2_DISABLE	0x53 //disable E2
#define EEPROM_ADDR_E2_ENABLE	(0x53|0x04) //enable E2	
#define EEPROM_I2C_LENGTH	8192

#define PASSWORD_LENGTH	4
#define SECTOR_SECURITY_STATUS_BASE_ADDR	0x800 //2048

#define LOCK_PROTECT_BIT		BIT0
#define WRITE_READ_PROTECT_BIT	BIT1
#define PASSWORD_CTRL_BIT		BIT3

#define I2C_PASSWORD_ADDR	2304
#define RF_PASSWORD_1_ADDR	2308
#define RF_PASSWORD_2_ADDR	2312
#define RF_PASSWORD_3_ADDR	2316
#define DSFID_ADDR			2320  	//1 byte
#define AFI_ADDR			2321	//1 byte
#define RFU_ADDR			2322	//2 bytes
#define UID_ADDR			2324	//8 bytes
#define UID_LENGTH			8
#define MEMORY_VOLUME_ADDR	2332	//3 bytes
#define IC_NUMBER_ADDR		2335	//1 byte


enum AccessMode{
	USER_MODE = 0x0,	// offer simple read/write access right
	ROOT_MODE = 0x1,	// offer password change access right
};

enum SectorAccessRight{
	//  	**********************************
	//  	*  submit passWd *   no submit   * 
	//b2,b1	*  Read * Write  *  Read * Write *
	// 00   *    1       1        1      0   *
	// 01   *	 1       1        1      1   *
	// 10   *	 1       1        0      0   *
	// 11   *	 0       1        0      0   *
	//      **********************************
	Access_1110	= 0,
	Access_1111 = 1,
	Access_1100 = 2,
	Access_0111 = 3,
};

enum SectorSelectPassWd{
	//00 => no passWd protect
	//01 => passWd 1
	//10 => passWd 2
	//11 => passwd 3
	noPassWd = 0,
	passWd_1 = 1,
	passWd_2 = 2,
	passWd_3 = 3,
};

class NfcTag
{
public:
	NfcTag(AccessMode mode = USER_MODE){
		if(mode == USER_MODE){
			eeAddr = EEPROM_ADDR_E2_DISABLE;
		}else{
			eeAddr = EEPROM_ADDR_E2_ENABLE;
		}
	};
	void init();
	void submitPassWd(byte* passWd);
	void writePassWd(byte* passWd);
	void sectorProtectConfig(unsigned int sectorNumber, bool protectEnable, SectorAccessRight accessRight = Access_1110, SectorSelectPassWd passWd = noPassWd);
	void clearSectorProtect(void);
	void sectorWriteSockConfig(unsigned int sectorNumber, bool sockEnable);
	byte getDSFID();
	byte getAFI();
	uint16_t getRFU();
	byte getUID(byte* buf);
	uint32_t getMemoryVolume();
	byte getICNumber();
	void clearMemory();
	void writeByte(unsigned int address, byte data);
	void writeBytes(unsigned int address, byte* buf, unsigned int len);
	byte readByte(unsigned int address);
	void readBytes(unsigned int address, byte* buf, unsigned int len);
	
private:
	int eeAddr;
	void _EEPROM_Write_Byte(unsigned int address, byte data);
	void _EEPROM_Write_Bytes(unsigned int address, byte* buf, unsigned int len);
	byte _EEPROM_Read_Byte(unsigned int address);
	unsigned int _EEPROM_Read_Bytes(unsigned int address, byte* buf, unsigned int len);
};
#endif