// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Robert Heller
//  Created       : Sat Nov 22 11:33:58 2025
//  Last Modified : <251122.1224>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (C) 2025  Robert Heller D/B/A Deepwoods Software
//			51 Locke Hill Road
//			Wendell, MA 01379-9728
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// 
//
//////////////////////////////////////////////////////////////////////////////

static const char rcsid[] = "@(#) : $Id$";

#include "NodeIdConfigurationGroup.hxx"

#include <cstring>

#include "stm32f_hal_conf.hxx"

#if defined (STM32F030x6) || defined (STM32F031x6) || defined (STM32F038xx) \
 || defined (STM32F030x8) || defined (STM32F030xC) || defined (STM32F042x6) \
 || defined (STM32F048xx) || defined (STM32F051x8) || defined (STM32F058xx)
static const size_t PAGE_SIZE = 0x400;
static const size_t BLOCK_SIZE = 4;
static const size_t BYTES_PER_BLOCK = 2;
#elif defined (STM32F070x6) || defined (STM32F070xB) || defined (STM32F071xB) \
   || defined (STM32F072xB) || defined (STM32F078xx) \
   || defined (STM32F091xC) || defined (STM32F098xx) \
   || defined (STM32F303xC) || defined (STM32F303xE)
static const size_t PAGE_SIZE = 0x800;
static const size_t BLOCK_SIZE = 4;
static const size_t BYTES_PER_BLOCK = 2;
#elif defined(STM32L432xx) || defined(STM32L431xx)
static const size_t PAGE_SIZE = 0x800;
static const size_t BLOCK_SIZE = 8;
static const size_t BYTES_PER_BLOCK = 4;
#define L4_FLASH
#elif defined(STM32F767xx)
// Note this assumes single-bank usage
static const size_t PAGE_SIZE = 256*1024;
static const size_t BLOCK_SIZE = 8;
static const size_t BYTES_PER_BLOCK = 4;
#define F7_FLASH
#elif defined(STM32G0B1xx)
// Note this assumes single-bank usage
static const size_t PAGE_SIZE = 0x800;
static const size_t BLOCK_SIZE = 8;
static const size_t BYTES_PER_BLOCK = 4;
#define L4_FLASH
#else
#error "stm32EEPROMEmulation unsupported STM32 device"
#endif

/// Linker-defined symbol where in the memory space (flash) the eeprom
/// emulation data starts.
extern const char __nodeid_start;
/// Linker-defined symbol where in the memory space (flash) the eeprom
/// emulation data ends.
extern const char __nodeid_end;

#define NODEID_FLASH_SIZE ((uintptr_t)(&__nodeid_end - &__nodeid_start))

#ifdef F7_FLASH
extern "C" {
extern const unsigned __stm32_eeprom_flash_sector_start;
}
#endif

static const uint8_t MAGICHEADER[] = {0xAB, 0xCD, 0xEF, 0x00};

void NodeIdMemoryConfigSpace::flash_write()
{
    uint8_t bdata[sizeof(MAGICHEADER+32)];
    memset(bdata,0,sizeof(bdata));
    memcpy(bdata,MAGICHEADER,sizeof(MAGICHEADER));
    strncpy((char *)(bdata+sizeof(MAGICHEADER)),id_.c_str(),32);
    uint32_t *data = (uint32_t *) bdata;
    const char* address = &__nodeid_start;
    uintptr_t uint_address = (uintptr_t)address;
    int count = (sizeof(MAGICHEADER)+32)/sizeof(uint32_t);
    while (count)
    {
        portENTER_CRITICAL();
        HAL_FLASH_Unlock();
#if defined(F7_FLASH)|| defined(L4_FLASH)
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, uint_address, *(uint64_t*)data);
#else        
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, uint_address, *data);
#endif        
        HAL_FLASH_Lock();
        portEXIT_CRITICAL();

        count -= BLOCK_SIZE;
        uint_address += BLOCK_SIZE;
        data += (BLOCK_SIZE / sizeof(uint32_t));
    }
        
}


void NodeIdMemoryConfigSpace::flash_read()
{
    const uint8_t *data = (const uint8_t *)&__nodeid_start;
    if (memcmp(MAGICHEADER,data,sizeof(MAGICHEADER)) == 0) 
    {
        char buffer[32];
        const char *p = (const char *)(data + sizeof(MAGICHEADER));
        for (int i = 0; i < 32; i++)
        {
            buffer[i] = *p++;
        }
        id_ = buffer;
    }
}


namespace utils
{

string node_id_to_string(uint64_t node_id)
{
    string result = "";
    char buffer[8];
    string dot = "";
    for (int i=0; i<6; i++)
    {
        snprintf(buffer,sizeof(buffer),"%02X",(unsigned)(node_id&0x0FF));
        result = buffer + dot + result;
        dot = ".";
        node_id >>= 8;
    }
    return result;
}

uint64_t string_to_uint64(const string node_string)
{
    uint64_t result = 0LL;
    for (int i=0; i<6; i++)
    {
        int index = i*3;
        unsigned byte=0;
        sscanf(node_string.substr(index,2).c_str(),"%02X",&byte);
        result <<= 8;
        result |= byte;
    }
    return result;
}


}

