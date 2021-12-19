#ifndef FHSS_H
#define FHSS_H

#include "common.h"

// we have 7 bit to set frequency, 0-125
uint8_t fhssFreq[] = {107,92,67,18,62,21,59,0,115,52,7,73,120,88,42,27,99,38,48,13,82,10,123,71,31};
uint16_t freqChangeSpeed = 8;
uint32_t fhssTransmitSpeed = 10;
struct  DataPacket {
    uint16_t a;
    uint16_t e;
    uint16_t t;
    uint16_t r;
    uint8_t  switches;  // 4 switches 2 bit each
} data_packet;

#endif // FHSS_H
