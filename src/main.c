#include "dma.h"
#include "timer.h"
#include "adc.h"
#include "dac.h"
#include "exti.h"
#include "uart.h"
#include <stdio.h>

int main() {

    config_eint0();
    config_timer_0();
    config_timer_1();
    config_adc();
    config_dac();
    configUART();
    config_dma();
    generate_sin();

    while(1) {
    	__WFI();
    }

    return 0;
}

