#ifndef ADC_H
#define ADC_H

#include <stm8s.h>

void initADC();
uint16_t getADCValue(uint8_t channel);

#endif // ADC_H
