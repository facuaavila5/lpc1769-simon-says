#ifndef TIMER_H
#define TIMER_H

#include "lpc17xx_timer.h"

#define TIMER0_MATCH_VALUE 1000

extern volatile uint8_t index_timer;
extern volatile uint8_t index_usuario;
// function prototypes
void config_timer_0(void);
void config_timer_1(void);

#endif

