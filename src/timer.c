#include "timer.h"
#include "dma.h"

/*
 * Refreshes display and updates pong and ball positions
 */
void config_timer_0(void) {
    TIM_TIMERCFG_Type timer0_cfg;
    TIM_MATCHCFG_Type match0_cfg;

    timer0_cfg.prescaleOption = TIM_USVAL;
    timer0_cfg.prescaleValue = 1000;

    match0_cfg.matchChannel = 0;
    match0_cfg.intOnMatch = ENABLE;
    match0_cfg.resetOnMatch = ENABLE;
    match0_cfg.stopOnMatch = ENABLE;
    match0_cfg.extMatchOutputType = TIM_NOTHING;
    match0_cfg.matchValue = TIMER0_MATCH_VALUE; // <--- Check val

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer0_cfg);
    TIM_ConfigMatch(LPC_TIM0, &match0_cfg);
}

void TIMER0_IRQHandler(void) {
    GPDMA_ChannelCmd(GPDMA_CHANNEL_0, DISABLE);
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
