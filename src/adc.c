#include "lpc17xx_adc.h"
#include "adc.h"

// Check uint16_t and uint32_t types
const uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
const uint16_t duty_cycles[] = {10, 20, 30, 40, 50};

void config_adc(void) {
    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);
    ADC_ChannelCmd(ADC_CHANNEL_0, ENABLE);
    ADC_ChannelCmd(ADC_CHANNEL_1, ENABLE);
    ADC_IntConfig(ADC_CHANNEL_0, ENABLE);
    ADC_IntConfig(ADC_CHANNEL_1, ENABLE);
    ADC_BurstCmd(ENABLE);
}

void ADC_IRQHandler(void) {
    uint16_t result;
    uint16_t *adc_ptr;

    if(ADC_ChannelGetStatus(ADC_CHANNEL_0, ADC_DATA_DONE)) {
        adc_ptr = (uint16_t *)ADC_0_RESULT_ADDRESS;
        result = ADC_ChannelGetData(ADC_CHANNEL_0);
        *adc_ptr = calc_frequency(conversion_data);
    }
    if(ADC_ChannelGetStatus(ADC_CHANNEL_1, ADC_DATA_DONE)) {
        adc_ptr = (uint16_t *)ADC_1_RESULT_ADDRESS;
        result = ADC_ChannelGetData(ADC_CHANNEL_1);
        *adc_ptr = calc_frequency(result);
    }
}

uint16_t calc_frequency(uint16_t conversion_data) {
    return notes[conversion_data / 512];
}

uint16_t calc_duty_cycle(uint16_t conversion_data) {
    
}
