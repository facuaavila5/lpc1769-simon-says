#ifndef ADC_H
#define ADC_H

#include "lpc17xx_adc.h"

#define ADC_RATE 200000
#define ADC_0_OUTPUT (uint32_t)(1 << 23)
#define ADC_1_OUTPUT (uint32_t)(1 << 24)
#define ADC_0_RESULT_ADDRESS (uint32_t)0x2007C000

// function prototypes
void config_adc(void);
uint16_t set_amplitude(uint16_t conversion_result);

#endif
