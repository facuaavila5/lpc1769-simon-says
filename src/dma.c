#include "dma.h"
#include "lpc17xx_dac.h"

#define TRANSFER_SIZE 100
#define SIN_VALUES_ADDRESS (uint32_t)0x2007C020 
#define DACR_ADDRESS (uint32_t)0x4008C000     

GPDMA_LLI_Type lli_dac;

void config_dma(void) {
   GPDMA_Channel_CFG_Type dac_dma;

    dac_dma.channelNum = GPDMA_CHANNEL_0; //Canal 0 para el dac 
    dac_dma.transferSize =  TRANSFER_SIZE;
    dac_dma.srcMemAddr = SIN_VALUES_ADDRESS;
    dac_dma.dstConn = GPDMA_DAC;
    dac_dma.transferType = GPDMA_M2P;
    dac_dma.linkedList = (uint32_t)&lli_dac; 
    //buffer circular para variar siempre entre las mismas frecuencias de las notas 

    lli_dac.srcAddr = SIN_VALUES_ADDRESS;
    lli_dac.dstAddr = DACR_ADDRESS;
    lli_dac.nextLLI = (uint32_t)&lli_dac;
    lli_dac.control = (TRANSFER_SIZE | (1<<18) | (1<<21) | (1<<26));
                       
    GPDMA_Init();
    GPDMA_Setup(&dac_dma);
}

void start_dac_dma(void) {
    DAC_SetDMATimeOut(567); // + Operacion para pasarlo a ticks
    GPDMA_ChannelCmd(GPDMA_CHANNEL_0, ENABLE);
}

