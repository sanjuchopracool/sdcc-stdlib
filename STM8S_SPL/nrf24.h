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
uint8_t nrfIsDataReady();
void nrfSetRegister( uint8_t inReg, uint8_t inRegData );
uint8_t nrfWrite(uint8_t *data, uint8_t count);
void nrfFlushTxFifo();
void nrfFlushRxFifo();
uint8_t nrfIsConnected();

typedef enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } NRF_POWER_LEVEL ;
typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } NRF_DATA_RATE;
void nrfSetPALevel (NRF_POWER_LEVEL level);
void nrfSetReceiveMode();
void nrfSetTransmitMode();
void nrfSetFixedDataSize(uint8_t dataSize);
int8_t nrfReadData( uint8_t *data, uint8_t count);
void nrfSetTxAddress(uint8_t address);
void nrfSetRxAddress(uint8_t address);
void nrfSetBindingAddress(uint8_t address);
void nrfSetFrequency(int8_t freq); // must be less <= 128
#endif // NRF24_H
