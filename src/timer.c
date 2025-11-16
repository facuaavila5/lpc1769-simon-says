#include "lpc17xx_timer.h"
#include "timer.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_uart.h"
#include <stdio.h>
#include "adc.h"

volatile uint8_t index_timer = 0;
volatile uint8_t index_usuario = 0;

void config_timer_0(void) {
    TIM_TIMERCFG_Type timer0_cfg;
    TIM_MATCHCFG_Type match0_cfg;

    timer0_cfg.prescaleOption = TIM_USVAL;
    timer0_cfg.prescaleValue = 1000;

    match0_cfg.matchChannel = 0;
    match0_cfg.intOnMatch = ENABLE;
    match0_cfg.resetOnMatch = ENABLE;
    match0_cfg.stopOnMatch = DISABLE; // pasa los 3 segundos y se detiene
    match0_cfg.extMatchOutputType = TIM_NOTHING;
    match0_cfg.matchValue = 700;

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer0_cfg);
    TIM_ConfigMatch(LPC_TIM0, &match0_cfg);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void config_timer_1(void) {
    TIM_TIMERCFG_Type timer1_cfg;
    TIM_MATCHCFG_Type match0_cfg;

    timer1_cfg.prescaleOption = TIM_USVAL;
    timer1_cfg.prescaleValue = 1000;

    match0_cfg.matchChannel = 0;
    match0_cfg.intOnMatch = ENABLE;
    match0_cfg.resetOnMatch = ENABLE;
    match0_cfg.stopOnMatch = DISABLE; // pasa los 3 segundos y se detiene
    match0_cfg.extMatchOutputType = TIM_NOTHING;
    match0_cfg.matchValue = 500;

    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timer1_cfg);
    TIM_ConfigMatch(LPC_TIM1, &match0_cfg);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

void TIMER0_IRQHandler(void) {
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

    if(sequence[index_timer] == 0) { //compara los timeouts
        // Llegamos al final de la secuencia
        index_timer = 0;
        GPDMA_ChannelCmd(GPDMA_CHANNEL_0, DISABLE);
        LPC_DAC->DACCTRL &= ~(1 << 3);
        NVIC_EnableIRQ(EINT0_IRQn); // vuelve a habilitar la interrupcion del boton.
        DAC_UpdateValue(0);
        TIM_Cmd(LPC_TIM0, DISABLE);
    }
    else {
        // Hay mas notas en la secuencia
    //	printf("else");
        turn_on_dac(sequence[index_timer]);
        index_timer++;
    }
    
}

void TIMER1_IRQHandler(void) {
	static uint32_t flag = 0;
    const uint16_t timeout_notes[7] = {954, 850, 757, 715, 636, 567, 505};
    TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);

    if(flag%2 == 0){
        turn_on_dac(timeout_notes[index_usuario]);
    }else{
    	GPDMA_ChannelCmd(GPDMA_CHANNEL_0, DISABLE);
		LPC_DAC->DACCTRL &= ~(1 << 3);
		DAC_UpdateValue(0);
		TIM_Cmd(LPC_TIM1, DISABLE);
    }
    flag++;

}
