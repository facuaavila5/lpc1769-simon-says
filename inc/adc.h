#ifndef ADC_H
#define ADC_H

#define ADC_RATE (uint32_t)200000
#define ADC_0_OUTPUT (uint32_t)(1 << 23)
#define ADC_1_OUTPUT (uint32_t)(1 << 24)
#define FREQUENCY_DIV (uint16_t)512
#define ADC_0_RESULT_ADDRESS (uint32_t)0x2007C000
#define ADC_1_RESULT_ADDRESS (uint32_t)0x2007C001

// function prototypes
void config_adc(void);

#endif
