#include "lpc17xx_adc.h"

#define ADC_RATE 200000
#define ADC_0_OUTPUT (uint32_t)(1 << 23)
#define ADC_1_OUTPUT (uint32_t)(1 << 24)

void config_adc(void) {
    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);
    ADC_BurstCmd(ENABLE);
    // Interruption or DMA?
}
