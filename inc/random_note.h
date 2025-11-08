#ifndef RANDOM_NOTE_H
#define RANDOM_NOTE_H

#include "LPC17xx.h"

#define NOTE_FREQ_ADDRESS (uint32_t)0x20080010

void generate_note(void);

#endif
