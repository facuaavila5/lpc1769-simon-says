#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include <stdio.h>
#include "adc.h"
#include "exti.h"
#include "timer.h"

void configUART(void);
void print_note(uint8_t note);

uint16_t user_input[20];
void configUART(void)
{
	// UART TX PIN CONFIGURATION
	PINSEL_CFG_Type TX_PIN;
	TX_PIN.portNum = 0;
	TX_PIN.pinNum = 2;
	TX_PIN.pinMode = PINSEL_TRISTATE;
	TX_PIN.funcNum = PINSEL_FUNC_1;
	TX_PIN.openDrain = PINSEL_OD_NORMAL;
	PINSEL_ConfigPin(&TX_PIN);

	PINSEL_CFG_Type RX_PIN;
	RX_PIN.portNum = 0;
	RX_PIN.pinNum = 3;
	RX_PIN.pinMode = PINSEL_TRISTATE;
	RX_PIN.funcNum = PINSEL_FUNC_1;
	RX_PIN.openDrain = PINSEL_OD_NORMAL;
	PINSEL_ConfigPin(&RX_PIN);

	//UART CONFIGURATION
	UART_CFG_Type uart0;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	UART_ConfigStructInit(&uart0); //lo mismo que arriba, pero se hace automaticamente (config por defecto)
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &uart0); //inicializa periferico

	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct); //inicializa FIFO

	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE); //habilita transmision

	// Habilitar interrupción de recepción
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UART_INTCFG_RBR, ENABLE);
	NVIC_EnableIRQ(UART0_IRQn);
}


// Interrupción de recepción UART0
void UART0_IRQHandler(void)
{
	uint8_t receivedData;
	static uint8_t incorrecto = 0;
	static uint8_t i = 0;
	    // Verificar si la interrupción fue por datos disponibles (RDA)
	    if (UART_GetIntId((LPC_UART_TypeDef *)LPC_UART0) & UART_IIR_INTID_RDA)
	    {
	        // Mientras haya datos en la FIFO, leerlos todos
	        while (UART_Receive((LPC_UART_TypeDef *)LPC_UART0, &receivedData, 1, NONE_BLOCKING))
	        {
	        	
				print_note(receivedData - 48);
				index_usuario = receivedData - 48;
				TIM_Cmd(LPC_TIM1, ENABLE);
				
				if(i< index_sequence_uart){
					if((receivedData-48) != secuencia_indices[i]){
						incorrecto = 1;
					}
					i++;
				}
				if(i == index_sequence_uart) {
					i = 0;
					if(incorrecto!=1){
						printf("\nMuy bien! Pasaste al siguiente nivel.\n");
						index_sequence++;
						note_generated = 0;
						fflush(stdout);
					}else{
						//index_sequence = 0;
						incorrecto = 0;
						printf("\nQue pena! Intentalo de vuelta.\n");
						fflush(stdout);
						// sequence = {0};
					}
				}


	        }
	    }
}

void print_note(uint8_t note) {
	switch(note) {
		case 0:
			printf("Do ");
			break;
		case 1:
			printf("Re ");
			break;
		case 2:
			printf("Mi ");
			break;
		case 3:
			printf("Fa ");
			break;
		case 4:
			printf("Sol ");
			break;
		case 5:
			printf("La ");
			break;
		case 6:
			printf("Si ");
			break;
		default:
			break;
	}
}
