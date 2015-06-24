/*
 * Copyright (c) 2015 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/30/2015
 */

#include "sram.h"

/**
 * setMode
 *
 * Set operation mode
 *
 * @param mode Operation mode
 */
void SRAM::setMode(char mode)
{
  if (mode != operationMode)
  {
    chipSelect(true);
    spi.transfer(WRSR);
    spi.transfer(mode);
    chipSelect(false);
    operationMode = mode;
  }
}

/**
 * readByte
 *
 * Read byte from SRAM
 *
 * @param address Memory address
 *
 * @return Byte read
 */
unsigned char SRAM::readByte(unsigned int address)
{
  unsigned char res;

  // Set byte mode
  setMode(BYTE_MODE);
  
  // Write address, read data
  chipSelect(true);
  spi.transfer(READ);
  spi.transfer((unsigned char)(address >> 8));
  spi.transfer((unsigned char)address);
  res = spi.transfer(0xFF);
  chipSelect(false);
  
  return res;
}

/**
 * writeByte
 *
 * Write byte to SRAM
 *
 * @param address Memory address
 * @param data Data byte to be written
 */
void SRAM::writeByte(unsigned int address, char data)
{
  // Set byte mode
  setMode(BYTE_MODE);
  
  // Write address, read data
  chipSelect(true);
  spi.transfer(WRITE);
  spi.transfer((unsigned char)(address >> 8));
  spi.transfer((unsigned char)address);
  spi.transfer(data);
  chipSelect(false);
}
