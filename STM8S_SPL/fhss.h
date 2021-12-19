#ifndef FHSS_H
#define FHSS_H

#include "common.h"

struct  DataPacket {
    uint16_t a;
    uint16_t e;
    uint16_t t;
    uint16_t r;
    uint8_t  switches;  // 4 switches 2 bit each
} data_packet;

#endif // FHSS_H
