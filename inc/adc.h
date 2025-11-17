#ifndef ADC_H
#define ADC_H

#include "lpc17xx_adc.h"

#define ADC_RATE 200000
#define ADC_0_OUTPUT (uint32_t)(1 << 23)
#define ADC_1_OUTPUT (uint32_t)(1 << 24)
#define ADC_0_RESULT_ADDRESS (uint32_t)0x2007C000

extern const uint16_t timeout_notes[7];
extern volatile uint16_t index;
extern volatile uint16_t sequence[20];
extern volatile uint16_t index_sequence;

extern volatile uint16_t index_sequence_uart;
extern volatile uint16_t secuencia_indices[20];

// function prototypes
void config_adc(void);
void turn_on_dac(uint16_t timeout);
uint16_t calc_timeout(uint16_t conversion_data);

#endif

