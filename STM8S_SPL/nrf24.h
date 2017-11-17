#ifndef NRF24_H
#define NRF24_H

#include <stm8s.h>

uint8_t nrfGetRegister(uint8_t inReg);
uint8_t mrfGetStatusRegister();
void nrfSetRegister( uint8_t inReg, uint8_t inRegData );
uint8_t nrfWrite(uint8_t *data, uint8_t count);

#endif // NRF24_H
