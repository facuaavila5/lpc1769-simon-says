#include "lpc17xx_dac.h"
#include "dac.h"

void config_dac(void) {
    DAC_Init();
    DAC_SetBias(DAC_700uA);

}
