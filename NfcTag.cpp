/*
  NfcTag.cpp
  
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

#include "NfcTag.h"

void NfcTag::init()
{
	Wire.begin();
}

void NfcTag::submitPassWd(byte* passWd)
{
	Wire.beginTransmission(eeAddr);
	Wire.write(0x09);
	Wire.write(0x00);

	for(int i = 0; i < PASSWORD_LENGTH; i++){
		Wire.write(passWd[i]);
	}
	Wire.write(0x09);
	for(int i = 0; i < PASSWORD_LENGTH; i++){
		Wire.write(passWd[i]);
	}
	Wire.endTransmission();// stop transmitting 
}

void NfcTag::writePassWd(byte* passWd)
{
	Wire.beginTransmission(eeAddr);
	Wire.write(0x09);
	Wire.write(0x00);

	for(int i = 0; i < PASSWORD_LENGTH; i++){
		Wire.write(passWd[i]);
	}
	Wire.write(0x07);
	for(int i = 0; i < PASSWORD_LENGTH; i++){
		Wire.write(passWd[i]);
	}
	Wire.endTransmission();    // stop transmitting 	
}

void NfcTag::sectorProtectConfig(unsigned int sectorNumber, bool protectEnable, SectorAccessRight accessRight, SectorSelectPassWd passWd)
{
	if(!protectEnable){
		_EEPROM_Write_Byte(sectorNumber,0x0);
	}else{
		_EEPROM_Write_Byte(sectorNumber,protectEnable|(accessRight<<1)|(passWd<<2));
	}
}

void NfcTag::clearSectorProtect(void)
{
	byte buf[64]={0x0};
	_EEPROM_Write_Bytes(0, buf, 64);
}


void NfcTag::sectorWriteSockConfig(unsigned int sectorNumber, bool sockEnable)
{
	unsigned int sectorAddress = SECTOR_SECURITY_STATUS_BASE_ADDR + (sectorNumber/8);
	byte sectorBit = sectorNumber%8;
	byte preStatus = _EEPROM_Read_Byte(sectorAddress);
	//bool status = (preStatus|(1<<sectorBit))>>sectorBit;
	bool status = (preStatus>>sectorBit)&0x01;
	if(status != sockEnable){
		if(status == true){
			writeByte(sectorAddress,preStatus&(~(1<<sectorBit)));
		}else{
			writeByte(sectorAddress,preStatus|(1<<sectorBit));
		}
	}
}


byte NfcTag::getDSFID()
{
	return _EEPROM_Read_Byte(DSFID_ADDR);
}

byte NfcTag::getAFI()
{
	return _EEPROM_Read_Byte(AFI_ADDR);
}

uint16_t NfcTag::getRFU()
{
	uint16_t rfu = 0x00;
	rfu = _EEPROM_Read_Byte(RFU_ADDR);
	return (rfu<<8|_EEPROM_Read_Byte(RFU_ADDR+1));
}

byte NfcTag::getUID(byte* buf)
{
	_EEPROM_Read_Bytes(UID_ADDR,buf,UID_LENGTH);	
	return UID_LENGTH;
}

uint32_t NfcTag::getMemoryVolume()
{
	uint32_t volume = 0x0;
	volume = _EEPROM_Read_Byte(MEMORY_VOLUME_ADDR);	
	volume = volume<<8|_EEPROM_Read_Byte(MEMORY_VOLUME_ADDR+1);
	volume = volume<<8|_EEPROM_Read_Byte(MEMORY_VOLUME_ADDR+2);
	return volume;
}

byte NfcTag::getICNumber()
{
	return _EEPROM_Read_Byte(IC_NUMBER_ADDR);	
}

void NfcTag::clearMemory()
{
	for(int i = 0; i < EEPROM_I2C_LENGTH; i++){
		writeByte(i,0x0);
	}
}

void NfcTag::writeByte(unsigned int address, byte data)
{
	_EEPROM_Write_Byte(address, data);
}

void NfcTag::writeBytes(unsigned int address, byte* buf, unsigned int len)
{
	_EEPROM_Write_Bytes(address, buf, len);
}

byte NfcTag::readByte(unsigned int address)
{
	return _EEPROM_Read_Byte(address);
}

void NfcTag::readBytes(unsigned int address, byte* buf, unsigned int len)
{
	_EEPROM_Read_Bytes(address, buf, len);
}

void NfcTag::_EEPROM_Write_Byte(unsigned int address, byte data)
{
	Wire.beginTransmission(eeAddr);
	Wire.write((int)(address >> 8)); 	// MSB 
	Wire.write((int)(address & 0xFF));// LSB 
	Wire.write(data);	// sends one byte  
	//delay(5);
	Wire.endTransmission();	// stop transmitting	
}

void NfcTag::_EEPROM_Write_Bytes(unsigned int address, byte* buf, unsigned int len)
{
	Wire.beginTransmission(eeAddr);
	Wire.write((int)(address >> 8)); 	// MSB 
	Wire.write((int)(address & 0xFF));// LSB 
	for(int i = 0; i < len; i++){
		Wire.write(buf[i]);	// sends one byte  
	}
	Wire.endTransmission();	// stop transmitting		
}

byte NfcTag::_EEPROM_Read_Byte(unsigned int address)
{
	byte rdata = 0x7F;
	Wire.beginTransmission(eeAddr); //Device Address
	Wire.write((int)(address >> 8)); // EEPROM_MSB
	Wire.write((int)(address & 0xFF)); // EEPROM_LSB
	Wire.endTransmission();
  
	Wire.beginTransmission(eeAddr);
	Wire.requestFrom(eeAddr,1);
  
	if (Wire.available()){
		rdata = Wire.read();
	}
	Wire.endTransmission();         // end transmission
	return rdata;	
}

unsigned int NfcTag::_EEPROM_Read_Bytes(unsigned int address, byte* buf, unsigned int len)
{
	byte rdata = 0x7F;
	Wire.beginTransmission(eeAddr); //Device Address
	Wire.write((int)(address >> 8)); // EEPROM_MSB
	Wire.write((int)(address & 0xFF)); // EEPROM_LSB
	Wire.endTransmission();
  
	Wire.beginTransmission(eeAddr);
	Wire.requestFrom(eeAddr,len);
  
	int i = 0;
	while(Wire.available()){
		buf[i++] = Wire.read();
	}
	Wire.endTransmission();         // end transmission
	return i;	
}