#ifndef PONG_H
#define PONG_H

#include "stdint.h"

#define ADDRESS_BANK_0 (uint32_t)0x2007C000
#define ADDRESS_BANK_1 (uint32_t)0x20080000

struct ball {
    int32_t pos_x, pos_y, speed_x, speed_y;

};

struct paddle {
    int32_t pos;
};

// function prototypes

#endif
