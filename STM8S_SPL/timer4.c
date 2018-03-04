#include "timer4.h"

#define TIM4_CR1 	*(__IO uint8_t*)0x5340
#define TIM4_IER 	*(__IO uint8_t*)0x5343
#define TIM4_EGR 	*(__IO uint8_t*)0x5345
#define TIM4_CNTR 	*(__IO uint8_t*)0x5346
#define TIM4_PSCR 	*(__IO uint8_t*)0x5347
#define TIM4_ARR 	*(__IO uint8_t*)0x5348

void setUpTimer4()
{
    // main clock 16 MHZ
    // prescaler 128 =  (2^PSCR)
    // timer clock 125KHz
    // Counter 250
    // interrupt at every 2ms

    TIM4_PSCR = 0x07;
    TIM4_ARR = 249;
    TIM4_IER = 0x01;
    TIM4_CR1 = 0x01;
}
