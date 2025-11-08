#ifndef DAC_H
#define DAC_H

#include "lpc17xx_dac.h"

#define DAC_OUTPUT (uint32_t)(1 << 26)
#define DAC_ARRAY_SIZE 100

// function prototypes
void config_dac(void);
void load_dac_values(void);

#endif
