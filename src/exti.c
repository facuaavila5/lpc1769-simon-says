#include "lpc17xx_exti.h"
#include "lpc17xx_pinsel.h"
#include "exti.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpdma.h"
#include "adc.h"
#include <stdio.h>

volatile uint8_t note_generated = 0;


void config_eint0(void) {
    PINSEL_CFG_Type eint0_pin = {0};
    EXTI_CFG_Type eint0_cfg = {0};
    
    //Configuracion de EINT0 para que suene la nota a adivinar  

    eint0_pin.portNum = PINSEL_PORT_2; 
    eint0_pin.pinNum = PINSEL_PIN_10;
    eint0_pin.funcNum = PINSEL_FUNC_1;
    eint0_pin.pinMode = PINSEL_PULLDOWN;
    PINSEL_ConfigPin(&eint0_pin);

    eint0_cfg.line = EXTI_EINT0;
    eint0_cfg.mode = EXTI_EDGE_SENSITIVE;
    eint0_cfg.polarity = EXTI_FALLING_EDGE;
    EXTI_Init();
    EXTI_ConfigEnable(&eint0_cfg); // esto ya hace nvic_enable
}

void EINT0_IRQHandler(void) {
    EXTI_ClearFlag(EXTI_EINT0);
    TIM_Cmd(LPC_TIM0, ENABLE);

    if(note_generated == 0) {
        ADC_StartCmd(ADC_START_NOW);
        note_generated = 1;
    }
}
