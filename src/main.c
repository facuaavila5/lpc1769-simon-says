#include "dma.h"
#include "timer.h"
#include "adc.h"
#include "dac.h"
#include "exti.h"

int main() {
    config_eint0();
    config_timer_0();
    config_adc();
    config_dac();
    load_dac_values();
    config_dma();

    while(1) {

    }

    return 0;
}
