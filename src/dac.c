#include "lpc17xx_dac.h"
#include "dac.h"

#define SIN_VALUES_ADDRESS (uint32_t ) 0x2007C020 



const uint16_t onda_sin [DAC_ARRAY_SIZE] = {
    512,544,576,607,638,668,697,724,751,776,
    800,822,843,861,878,893,906,916,925,931,
    935,937,937,935,931,925,917,906,894,879,
    863,844,824,802,778,752,726,698,669,639,
    608,577,545,513,481,449,418,387,357,328,
    300,273,248,223,200,178,157,139,122,107,
    94,84,75,69,65,63,63,65,69,75,
    84,94,107,122,139,157,178,200,223,248,
    273,300,328,357,387,418,449,481,513,545,
    577,608,639,669,698,726,752,778,802,824
}; 
/*  
    Vamos a tener 100 valores de muestras por ciclo porque sino no llegamos a la frecuencia deseada. 
    ya que deberiamos refrescar el dac en menos de un microseg 

    Frecuencias de las Notas:   
    - Do - 261.63 Hz 
    - Re - 293.66 Hz
    - Mi - 329.63 Hz     
    - Fa - 349.23 Hz  
    - Sol - 392.00 Hz
    - La - 440.00 Hz
    - Si - 493.88 Hz     
    
    Tenemos como max 500 Hz  
    
*/ 

void config_dac(void) {
    DAC_Init();
    DAC_SetBias(DAC_700uA);

}
 
void load_dac_values(uint16_t value) {
    uint16_t *puntero_dac = (uint16_t *) SIN_VALUES_ADDRESS;
    // puntero a la direccion de memoria del banco 0 

    for (uint8_t i = 0 ; i < DAC_ARRAY_SIZE; i++) {
            *puntero_dac = onda_sin[i];
            puntero_dac ++; 

    }

}

void set_frequency (void) {
    uint8_t *freq_ptr = (uint8_t *) ;// FIXME (ver que direccion puso facu) 
    

}