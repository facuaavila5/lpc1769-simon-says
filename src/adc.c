#include "lpc17xx_adc.h"
#include "adc.h"

const uint16_t factor[] = {1/2, 1, 2};

void config_adc(void) {
    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_ChannelCmd(ADC_CHANNEL_0, ENABLE);
    ADC_IntConfig(ADC_CHANNEL_0, ENABLE);
}

void ADC_IRQHandler(void) {
    uint16_t result;
    uint16_t *adc_ptr;

    if(ADC_ChannelGetStatus(ADC_CHANNEL_0, ADC_DATA_DONE)) {
        adc_ptr = (uint16_t *)ADC_0_RESULT_ADDRESS;
        *adc_ptr = calc_frequency(ADC_ChannelGetData(ADC_CHANNEL_0));
    }
}

uint16_t calc_frequency(uint16_t conversion_data) {
    return factor[conversion_data / 512];
}

uint16_t calc_duty_cycle(uint16_t conversion_data) {
    
}
