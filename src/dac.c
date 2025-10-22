#include "lpc17xx_dac.h"

#define DAC_OUTPUT (uint32_t)(1 << 26)

void config_dac(void) {
    DAC_Init();
    DAC_SetBias(DAC_700uA);

}
