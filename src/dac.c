#include "lpc17xx_dac.h"
#include "dac.h"

void config_dac(void) {
    DAC_CONVERTER_CFG_Type dma_dac_cfg;

    dma_dac_cfg.doubleBufferEnable = ENABLE;
    dma_dac_cfg.dmaEnable = ENABLE;
    dma_dac_cfg.counterEnable = ENABLE;

    DAC_Init();
    DAC_ConfigDAConverterControl(&dma_dac_cfg);
}
