#include "lpc17xx_gpdma.h"
#include "dma.h"
#include "math.h"

#define TRANSFER_SIZE 100
#define DAC_MAX 1023
#define PI 3.141592

void generate_sin(void);

uint16_t onda_sin [TRANSFER_SIZE];

GPDMA_LLI_Type lli_dac = {0};

void config_dma(void) {
    GPDMA_Channel_CFG_Type dac_dma = {0};

    dac_dma.channelNum = GPDMA_CHANNEL_0;
    dac_dma.transferSize = TRANSFER_SIZE;
    dac_dma.srcMemAddr = (uint32_t)&onda_sin[0];
    // dac_dma.dstMemAddr = (uint32_t)&LPC_DAC->DACR;
    dac_dma.transferType = GPDMA_M2P;
    dac_dma.dstConn = GPDMA_DAC;
    dac_dma.linkedList =(uint32_t) &lli_dac;

    lli_dac.srcAddr = (uint32_t)&onda_sin[0];
    lli_dac.dstAddr = (uint32_t)&LPC_DAC->DACR;
    lli_dac.nextLLI = (uint32_t) &lli_dac;
    lli_dac.control = (TRANSFER_SIZE | (1<<18) | (1<<21) | (1<<26));

    GPDMA_Init();
    GPDMA_Setup(&dac_dma);
}

void generate_sin(void) {
    for (uint32_t i = 0; i < TRANSFER_SIZE; i++) {
        // Calcula el ángulo (de 0 a 2π)
        float angle = 2.0f * PI * i / TRANSFER_SIZE;
        // Calcula el valor sinusoidal entre -1.0 y +1.0
        float sine_value = sinf(angle);
        // Escala el valor a 0–1023 (10 bits del DAC)
        uint32_t dac_10bit = (uint32_t)((sine_value + 1.0f) * (DAC_MAX / 2.0f));
        // Desplaza 6 bits a la izquierda (bits [15:6] del DACR)
        onda_sin[i] = dac_10bit << 6;
    }
}

