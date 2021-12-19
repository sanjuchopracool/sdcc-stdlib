#include "utility.h"

char *baseAddress = (char *) 0x4000;        //  EEPROM base address.
#define FLASH_DUKR 	*(__IO uint8_t*)0x5064
#define FLASH_IAPSR *(__IO uint8_t*)0x505F

uint8_t readEEPROMAddress()
{
    if ((FLASH_IAPSR & FLASH_IAPSR_DUL) == 0)
    {
        FLASH_DUKR = 0xae;
        FLASH_DUKR = 0x56;
        while((FLASH_IAPSR & FLASH_IAPSR_DUL) == 0);
    }
    return *baseAddress;
}

void writeEEPROMAddress(uint8_t address)
{
    *baseAddress = address;
}
