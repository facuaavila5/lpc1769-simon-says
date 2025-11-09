#include "adc.h"
#include "timer.h"
#include "dma.h"

const uint16_t factor[] = {1/2, 1, 2};

void config_adc(void) {
    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_ChannelCmd(ADC_CHANNEL_0, ENABLE);
    ADC_IntConfig(ADC_CHANNEL_0, ENABLE);
}

void ADC_IRQHandler(void) {
    if(ADC_ChannelGetStatus(ADC_CHANNEL_0, ADC_DATA_DONE)) {
        uint16_t result = ADC_ChannelGetData(ADC_CHANNEL_0);
        uint16_t *adc_ptr = (uint16_t *)ADC_0_RESULT_ADDRESS;
        *adc_ptr = set_amplitude(result);

        TIM_Cmd(LPC_TIM0, ENABLE);
        start_dac_dma();
    }
}

uint16_t set_amplitude(uint16_t conversion_result) {
    return (uint16_t)1; // change 512
}
