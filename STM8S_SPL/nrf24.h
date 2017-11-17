#ifndef NRF24_H
#define NRF24_H

#include <stm8s.h>

#define REG_STATUS                0x07

// STATUS register:
#define STATUS_TX_FULL        (1<<0)
#define STATUS_RX_P_NO        (0x7<<1)
#define STATUS_MAX_RT         (1<<4)
#define STATUS_TX_DS          (1<<5)
#define STATUS_RX_DR          (1<<6)


void initNrf();
uint8_t nrfGetRegister(uint8_t inReg);
uint8_t nrfGetStatusRegister();
void nrfSetRegister( uint8_t inReg, uint8_t inRegData );
uint8_t nrfWrite(uint8_t *data, uint8_t count);
void nrfFlushTxFifo();

#endif // NRF24_H
