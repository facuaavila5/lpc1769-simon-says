#include "random_note.h"
#include "lpc17xx_systick.h"
#include <stdlib.h>


#define RANDOM_NUMBER_MASK  0b00000111 //mascara para tener solo los ultimos 3
#define NOTES_SIZE 256 
// NOTE_FREQ_ADDRESS 

const uint16_t frequency[] = {262, 294, 330, 349, 392, 440, 494, 523}; // notas 
const uint16_t timeout_dac [] = {953,849,757,715,637,567,505,477}; // valor para el time out 
uint8_t level = 0; // nivel del juego en el que estamos  
const uint32_t notes[NOTES_SIZE] = {}; // se van guardando las notas que se van reproduciendo 
uint8_t random_number; // num random que generamos 
uint32_t adc_conver ; 


void generate_note(void) {
    uint16_t *freq_addrs_ptr = (uint16_t *) NOTE_FREQ_ADDRESS;  // puntero a la direccion de memoria 

    
        notes[level-1] = frequency[random_number]; // guardamos la nota que toco 
       *freq_addrs_ptr = notes; // lo guardo en la memoria 
        
    
}

void generate_random (){
    // tomo la conversion del adc para generar el num random 
    adc_conver = (LPC_ADC -> ADDR0 >> 4) & 0x0FFF;  
    random_number = adc_conver & RANDOM_NUMBER_MASK;  // me quedo con 3 bits 
     
}


/*
void cfgSystick(){
    /* Empieza para interrumpir cada 100ms
        tick = (frecuencia 100 Mhz * 100ms ) - 1 
        tick = 9 999 999 

     
   SysTick -> LOAD = 9999999;
   SysTick -> VAL = 0; 
   SysTick -> CTRL = 0b00000101; //Interrupcion deshabilitada  

    ;
}
 */

 