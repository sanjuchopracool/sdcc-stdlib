#ifndef LED_H
#define LED_H

#include "common.h"

void initLED()
{
    // LED
    {
        //PB5
        PB_DDR |= 0x20; // Direction
        PB_CR1 |= 0x20; // Push pull (Required)
        PB_CR2 |= 0x20; // Fast (10MHz)
    }
}

void toggleLED()
{

    PB_ODR ^= 0x20;
}

void offLED()
{
    PB_ODR |= 0x20;
}

void onLED()
{
    PB_ODR &= 0xDF;
}
#endif // LED_H
