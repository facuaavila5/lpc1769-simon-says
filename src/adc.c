#include "lpc17xx_adc.h"
#include "adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "uart.h"
#include <stdio.h>
#include "dma.h"
#define RANDOM_NUMBER_MASK  0b00000111

void config_pcb_adc(void);
void turn_on_dac(uint16_t timeout);

uint16_t calc_timeout(uint16_t conversion_data);
const uint16_t timeout_notes[7] = {954, 850, 757, 715, 636, 567, 505};
volatile uint16_t index = 0; //índice de nota generada
volatile uint16_t sequence[20] = {0}; //secuencia actual del timeout
volatile uint16_t index_sequence = 0;	//índice para el arreglo sequence[]
volatile uint16_t secuencia_indices[20] = {0}; //arreglo que guarda los indices de las notas generadas anteriormente

volatile uint16_t index_sequence_uart = 0; //índice para comparar el arreglo de notas generadas con el arreglo de notas ingresadas por el user.



void config_adc(void) {
    config_pcb_adc();
    ADC_Init(ADC_RATE);
    ADC_ChannelCmd(ADC_CHANNEL_0, ENABLE);
    ADC_IntConfig(ADC_CHANNEL_0, ENABLE);
    NVIC_SetPriority(ADC_IRQn, 31);
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void) {
	if(ADC_ChannelGetStatus(ADC_CHANNEL_0, ADC_DATA_DONE)) {
	        uint16_t result = ADC_ChannelGetData(ADC_CHANNEL_0);
	        uint16_t timeout = calc_timeout(result);
	        sequence[index_sequence] = timeout;
	}
}

void turn_on_dac(uint16_t timeout) {
        DAC_Init();
        DAC_SetDMATimeOut(timeout);
        LPC_DAC->DACR = 0;
        config_dma();
        GPDMA_ChannelCmd(GPDMA_CHANNEL_0, DISABLE);
        GPDMA_ChannelCmd(GPDMA_CHANNEL_0, ENABLE);
}

uint16_t calc_timeout(uint16_t conversion_data) {
	const uint8_t num_notes = sizeof(timeout_notes) / sizeof(timeout_notes[0]);
	uint16_t scaled = conversion_data >> 7;  // divide por 128
	index = scaled % num_notes;

	if (index >= num_notes)
		index = num_notes - 1;

	secuencia_indices[index_sequence_uart] = index;
	index_sequence_uart++;
	return timeout_notes[index];
}

void config_pcb_adc(void) {
    PINSEL_CFG_Type adc_pinsel = {0};

    adc_pinsel.portNum = 0;
    adc_pinsel.pinNum = 23;
    adc_pinsel.funcNum = PINSEL_FUNC_1;
    adc_pinsel.pinMode = PINSEL_TRISTATE;
    adc_pinsel.openDrain = PINSEL_OD_NORMAL; // aca no me acuerdo

    PINSEL_ConfigPin(&adc_pinsel);
}
