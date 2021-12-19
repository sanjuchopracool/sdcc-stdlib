#ifndef FHSS_H
#define FHSS_H

#include "common.h"

// we have 7 bit to set frequency, 0-128
uint8_t fhssFreq[] = {63,37,101,90,10,36,98,62,115,50,14,59,107,120,38,97,70,41,22,35};
struct  DataPacket {
    uint16_t a;
    uint16_t e;
    uint16_t t;
    uint16_t r;
    uint8_t  switches;  // 4 switches 2 bit each
} data_packet;

#endif // FHSS_H
