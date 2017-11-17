#ifndef SPI_H
#define SPI_H

#include <stm8s.h>

void initSPI();
uint8_t spiWriteRead(uint8_t inData);

#endif // SPI_H
