#include "lpc17xx_exti.h"
#include "lpc17xx_pinsel.h"
#include "exti.h"

void config_eint0(void) {
    PINSEL_CFG_Type eint0_pin = {0};
    EXTI_CFG_Type eint0_cfg = {0};

    eint0_pin.portNum = PINSEL_PORT_2;
    eint0_pin.pinNum = PINSEL_PIN_10;
    eint0_pin.funcNum = PINSEL_FUNC_1;
    eint0_pin.pinMode = PINSEL_PULLDOWN;
    PINSEL_ConfigPin(&eint0_pin);

    eint0_cfg.line = EXTI_EINT0;
    eint0_cfg.mode = EXTI_EDGE_SENSITIVE;
    eint0_cfg.polarity = EXTI_FALLING_EDGE;
    EXTI_Init();
    EXTI_ConfigEnable(&eint0_cfg);
}

/*
 * Triggers ADC conversion in case its on start mode.
 * If burst mod is enabled, sends signal through PWM1, and
 * generates note based on AD0.0 frequency 
 */
void config_eint1(void) {
    PINSEL_CFG_Type eint1_pin = {0};
    EXTI_CFG_Type eint1_cfg = {0};

    eint1_pin.portNum = PINSEL_PORT_2;
    eint1_pin.pinNum = PINSEL_PIN_11;
    eint1_pin.funcNum = PINSEL_FUNC_1;
    eint1_pin.pinMode = PINSEL_PULLDOWN;
    PINSEL_ConfigPin(&eint1_pin);

    eint1_cfg.line = EXTI_EINT0;
    eint1_cfg.mode = EXTI_EDGE_SENSITIVE;
    eint1_cfg.polarity = EXTI_FALLING_EDGE;
    EXTI_Init();
    EXTI_ConfigEnable(&eint1_cfg);
}

/*
 * Sends PWM1 signal output to Buzzer, with the corresponding
 * frequency and duty cycle.
 */
void EINT1_IRQHandler(voidº) {


}
