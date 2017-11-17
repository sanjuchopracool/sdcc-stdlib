#ifndef TIMER4_H
#define TIMER4_H

#include <stm8s.h>

#define TIM4_SR 	*(__IO uint8_t*)0x5344

void setUpTimer4();

#endif // TIMER4_H
