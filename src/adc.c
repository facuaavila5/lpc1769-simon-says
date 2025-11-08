#include "lpc17xx_adc.h"
#include "adc.h"

void config_adc(void) {
    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);
    ADC_BurstCmd(ENABLE);
    // Interruption or DMA?
}

