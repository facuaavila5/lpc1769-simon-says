#include "configs.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_exti.h"

#define ADC_RATE 200000

void config_pcb(void) {

}

void config_adc(void) {
    DAC_CONVERTER_CFG_Type dac_dma_cfg;

    ADC_Init(ADC_RATE);
    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);
    ADC_BurstCmd(ENABLE);
    // Interruption or DMA?
}

void config_dma(void) {
    GPDMA_Channel_CFG_Type adc_0, adc_1;

}

void config_dac(void) {
    
    DAC_Init();
    DAC_SetBias(DAC_700uA);

}

void config_eint0(void) {
    PINSEL_CFG_Type eint0_pin = {0};
    EXTI_CFG_Type eint0_cfg = {0};

    eint0_pin.portNum = PINSEL_PORT_2;
    eint0_pin.pinNum = PINSEL_PIN_10;
    eint0_pin.funcNum = PINSEL_FUNC_1;
    eint0_pin.pinMode = PINSEL_PULLDOWN;
    PINSEL_ConfigPin(&eint0_pin);

    eint0_cfg.EXTI_LINE = EXTI_EINT0;
    eint0_cfg.EXTI_MODE = EXTI_EDGE_SENSITIVE;
    eint0_cfg.EXTI_POLARITY = EXTI_FALLING_EDGE;
    EXTI_Init();
    EXTI_ConfigEnable(&eint0_cfg); // Config or ConfigEnable??
    // Nvic?
}

/*
 * Refreshes display and updates pong and ball positions
 */
void config_timer_0(void) {
    TIM_TIMERCFG_Type timer0_cfg;
    TIM_MATCHCFG_Type match0_cfg;

    timer0_cfg.prescaleOption = TIM_USVAL;
    timer0_cfg.prescaleValue = 1; // 1us

    match0_cfg.matchChannel = 0;
    match0_cfg.intOnMatch = ENABLE;
    match0_cfg.resetOnMatch = ENABLE;
    match0_cfg.stopOnMatch = DISABLE;
    match0_cfg.extMatchOutputType = TIM_NOTHING;
    match0_cfg.matchValue = 10; // <--- Check val

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer0_cfg);
    TIM_ConfigMatch(LPC_TIM0, &match0_cfg);
    
}

/*
 * Verifies ball collision or ball out of edge
 */
void config_timer_1(void) {
    TIM_TIMERCFG_Type timer1_cfg;
    TIM_MATCHCFG_Type match0_cfg;

    timer1_cfg.prescaleOption = TIM_USVAL;
    timer1_cfg.prescaleValue = 1; // 1us

    match0_cfg.matchChannel = 0;
    match0_cfg.intOnMatch = ENABLE;
    match0_cfg.resetOnMatch = ENABLE;
    match0_cfg.stopOnMatch = DISABLE;
    match0_cfg.extMatchOutputType = TIM_NOTHING;
    match0_cfg.matchValue = 50; // <--- Check val

    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timer1_cfg);
    TIM_ConfigMatch(LPC_TIM1, &match0_cfg);
}
