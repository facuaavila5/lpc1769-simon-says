#include "lpc17xx_timer.h"

#define TIMER0_MATCH_VALUE 10
#define TIMER1_MATCH_VALUE 50

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
    match0_cfg.matchValue = TIMER0_MATCH_VALUE; // <--- Check val

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
    match0_cfg.matchValue = TIMER1_MATCH_VALUE; // <--- Check val

    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timer1_cfg);
    TIM_ConfigMatch(LPC_TIM1, &match0_cfg);
}
