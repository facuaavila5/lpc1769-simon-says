#include "pwm.h"
#include "lpc17xx_pwm.h"

#define DEFAULT_FREQUENCY 200
#define DEFAULT_DUTY_CYCLE 50

void config_pwm(void) {
    PWM_TIMERCFG_Type timer_cfg;
    PWM_MATCHCFG_Type match0, match1;

    timer_cfg.PrescaleOption = PWM_TICKVAL;
    timer_cfg.PrescaleValue = 0;

    // Match 0 for PWM frequency
    match0.matchChannel = 0;
    match0.resetOnMatch = ENABLE;
    match0.intOnMatch = DISABLE;
    match0.stopOnMatch = DISABLE;
    match0.matchValue = DEFAULT_FREQUENCY;
    // Match 1 for PWM duty cycle
    match1.matchChannel = 1;
    match0.resetOnMatch = ENABLE;
    match0.intOnMatch = DISABLE;
    match0.stopOnMatch = DISABLE;
    match0.matchValue = DEFAULT_DUTY_CYCLE;

    PWM_Init(PWM_TIM_MODE, &timer_cfg);
    PWM_ConfigMatch(&match0);
    PWM_ConfigMatch(&match1);
    PWM_ChannelCmd(PWM_CHANNEL_1);
    //PWM_Cmd(ENABLE);
}

void set_note(int frequency) {
    PWM_MatchUpdate(PWM_MATCH_0, (uint32_t)frequency, PWM_UPDATE_NOW);
}

void set_volume(int duty_cycle) {
    PWM_MatchUpdate(PWM_MATCH_1, (uint32_t)duty_cycle, PWM_UPDATE_NOW);
}
