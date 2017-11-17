#include "adc.h"

#define ADC1_CSR    *(__IO uint8_t*)0x5400
#define ADC1_CR1    *(__IO uint8_t*)0x5401
#define ADC1_CR2    *(__IO uint8_t*)0x5402
#define ADC1_CR3    *(__IO uint8_t*)0x5403
#define ADC1_DRH    *(__IO uint8_t*)0x5404
#define ADC1_DRL    *(__IO uint8_t*)0x5405
#define ADC1_TDRH    *(__IO uint8_t*)0x5406
#define ADC1_TDRL   *(__IO uint8_t*)0x5407
#define ADC1_HTRH   *(__IO uint8_t*)0x5408
#define ADC1_HTRL    *(__IO uint8_t*)0x5409
#define ADC1_LTRH   *(__IO uint8_t*)0x540A
#define ADC1_LTRL   *(__IO uint8_t*)0x540B
#define ADC1_AWSRH   *(__IO uint8_t*)0x540C
#define ADC1_AWSRL  *(__IO uint8_t*)0x540D
#define ADC1_AWCRH  *(__IO uint8_t*)0x540E
#define ADC1_AWCRL  *(__IO uint8_t*)0x540F


#define ADC1_CR1_ADON    ((uint8_t)0x01) /*!< A/D Converter on/off mask */
#define ADC1_FLAG_EOC    (uint8_t)0x80  /**< EOC falg */

void initADC()
{
    // ADC related stuff
    // Default value is fine input pins
    // Fmster/4, single conversion mode, enable ADC
    ADC1_CR1 = 0x21;
}

uint16_t getADCValue(uint8_t channel)
{
    uint16_t value;
    // i ma using reset value for adc1
    // so i can directly set channel value to CST
    ADC1_CSR = channel;        // set channel
    ADC1_CR1 |= ADC1_CR1_ADON; // start conversion

    while(! (ADC1_CSR & ADC1_FLAG_EOC) );
    //    // MSB at High and LSB at LOW
    value = (uint16_t)(ADC1_DRL | (uint16_t)ADC1_DRH << 2);
    ADC1_CSR &= (~ADC1_FLAG_EOC);
    return value;
}
