#ifndef ADC_H
#define ADC_H

#define ADC_RATE 200000
#define ADC_0_OUTPUT (uint32_t)(1 << 23)
#define ADC_1_OUTPUT (uint32_t)(1 << 24)

// function prototypes
void config_adc(void);

#endif
