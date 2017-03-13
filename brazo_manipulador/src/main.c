/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple blink example.
 */

/** \addtogroup blink Bare-metal blink example
 ** @{ */

/*==================[inclusions]=============================================*/



//#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
//#include "ciaaPOSIX_string.h" /* <= string header */


#include "main.h"

/*==================[macros and definitions]=================================*/
#define LPC_UART 	LPC_USART2
#define UARTx_IRQn  USART2_IRQn

/* Ring buffer size */
#define UART_RB_SIZE 256

/*==================[internal data declaration]==============================*/

/* Transmit and receive ring buffers */
static RINGBUFF_T txring, rxring;

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RB_SIZE], txbuff[UART_RB_SIZE];
const uint8_t MSG_INIT[] = "Manipulador de placas\r\n";

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/** @brief delay function
 * @param t desired milliseconds to wait
 */
static void pausems(uint32_t t);

/*==================[internal data definition]===============================*/

/** @brief used for delay counter */
static uint32_t pausems_count;

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/
/**
 * @brief	UART interrupt handler sub-routine
 * @return	Nothing
 */
void UART2_IRQHandler(void)
{
	Chip_UART_IRQRBHandler(LPC_UART, &rxring, &txring);
}


/*==================[internal functions definition]==========================*/

static void initHardware(void)
{

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000); // cada cuantos tics de reloj tiene que generar la interrupcion. EN este caso cada un ms
	/* Usa la base de tiempo del procesador (con el contador de 24 bits),
	 * es decir, cuenta 200M / 1000 en este caso, y ahi te queda 1ms
	 * */
	Board_Init();
	incializarPuertos();
    Board_UART_Init(LPC_UART);
}

static void pausems(uint32_t t)
{
	pausems_count = t;
	while (pausems_count != 0) {
		__WFI();
	}
}

/*==================[external functions definition]==========================*/

void SysTick_Handler(void)
{
	if(pausems_count > 0) pausems_count--;
}

int main(void)
{
	initHardware();
	pausems(100);
	uint8_t salidaUART;

	Chip_UART_SetBaud(LPC_UART, 115200);
	Chip_UART_ConfigData(LPC_UART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT); /* Default 8-N-1 */
		/* Enable UART Transmit */
	Chip_UART_TXEnable(LPC_UART);

		/* Reset FIFOs, Enable FIFOs and DMA mode in UART */
	Chip_UART_SetupFIFOS(LPC_UART, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
								UART_FCR_TX_RS | UART_FCR_TRG_LEV0));

		/* Enable UART Rx & line status interrupts */
		/*
		 * Do not enable transmit interrupt here, since it is handled by
		 * UART_Send() function, just to reset Tx Interrupt state for the
		 * first time
		 */
	Chip_UART_IntEnable(LPC_UART, (UART_IER_RBRINT));

		/* Before using the ring buffers, initialize them using the ring
		   buffer init function */
	RingBuffer_Init(&rxring, rxbuff, 1, UART_RB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_RB_SIZE);

		/* Enable Interrupt for UART channel */
		/* Priority = 1 */
	NVIC_SetPriority(UARTx_IRQn, 1);
		/* Enable Interrupt for UART channel */
	NVIC_EnableIRQ(UARTx_IRQn);
	//Chip_UART_SendRB(LPC_UART,&txring,&MSG_INIT,sizeof(MSG_INIT));

	//int32_t led,cont = 0;

	//led = LED;
	uint8_t strinit[] = "Sistema inicializado ... ";
	DEBUGSTR(strinit);
	//uint8_t str[64];

	BrazoState maquina = {.en_state = WAITING, .m_state = MANIPULATOR_HOLDING, .distance = 0, .msg=""};
	//cambiarEngState(&maquina,WAITING);
	//cambiarManipState(&maquina,MANIPULATOR_HOLDING);
	showState(&maquina);
	int len;
	uint32_t cont = 0;
	uint8_t buffer[1];
	uint8_t butStat;// = 0x00;
	uint8_t strinit2[] = " --> ahora vemos q pasa x aqui.... \r \n \r\n";

	engine_states engState_prev;// = maquina.en_state;
	manip_states manipState_prev;// = maquina.m_state;
	while (1)
	{
		buffer[0] = ' ';
		butStat = 0x00;
		engState_prev = maquina.en_state;
		manipState_prev = maquina.m_state;

		butStat = Button_GetStatus();
		len = Chip_UART_ReadRB(LPC_UART, &rxring, &buffer, sizeof(buffer));
		Chip_UART_SendRB(LPC_UART, &txring, &buffer, len);

		//sprintf(strinit2,"vuelta nro: %"PRIu32"-->\r\n ",cont);
		//DEBUGSTR(strinit2);
		if(buffer[0] == 'c')
		{
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 1);
			butStat = 0xFF;//BUTTONS_EN_AIR;
			sprintf(strinit2," Entrada --> %"PRIu32"--> enable air\r\n ",butStat);
			DEBUGSTR(strinit2);
		}
		else if(buffer[0] == 'l')
		{
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 0);
			butStat = 0xFF;//BUTTONS_DIS_AIR;
			sprintf(strinit2," Entrada --> %"PRIu32"--> dis air\r\n ",butStat);
			DEBUGSTR(strinit2);
		}
		else if(buffer[0] == 's')
		{
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 1);


			butStat = 0xFF;//BUTTONS_UP;
			sprintf(strinit2," Entrada -->  %"PRIu32"--> subir \r\n ",butStat);
			DEBUGSTR(strinit2);
		}
		else if(buffer[0] == 'b')
		{
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 1);
			butStat = 0xFF;//BUTTONS_DOWN;
			sprintf(strinit2," Entrada-->  %"PRIu32"-->bajar \r\n ",butStat);
			DEBUGSTR(strinit2);
		}
		else if(buffer[0] == 'p')
		{
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
			Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
			butStat = 0xFF;//BUTTONS_STOP;
			sprintf(strinit2," Entrada --> %"PRIu32"--> parar motor \r\n ",butStat);
			DEBUGSTR(strinit2);
		}
		else if(buffer[0] == 'q')
			showState(&maquina);
		switch(butStat)
		{
			case BUTTONS_STOP: // 1
				cambiarEngState(&maquina,WAITING);
				//showState(&maquina);
				break;
			case BUTTONS_UP: // 2
				cambiarEngState(&maquina,ENGINE_UP); // 1
				//showState(&maquina);
				break;
			case BUTTONS_DOWN: // 4
				cambiarEngState(&maquina,ENGINE_DOWN); // 2
			//	showState(&maquina);
				break;
			case BUTTONS_EN_AIR: // 8
				cambiarManipState(&maquina,MANIPULATOR_HOLDING);
				showState(&maquina);
		//		break;
			case BUTTONS_DIS_AIR: // 16
				cambiarManipState(&maquina,MANIPULATOR_FREE);
				showState(&maquina);
				break;
			default:
				break;
		}
		if ((engState_prev != maquina.en_state) || (manipState_prev != maquina.m_state) )
			showState(&maquina);
		/*sprintf(str,"asda: %"PRIu32"-->\r\n ",butStat);
		DEBUGSTR(str);
		sprintf(str,"Evento nro: %"PRIu32"\r\n",cont);
		cont++;
		DEBUGSTR(str);

		Board_LED_Toggle(LED);*/
		//sprintf(strinit2,"vuelta nro: %"PRIu32"-->\r\n ",cont);
		//DEBUGSTR(strinit2);
		//pausems(1);
		//pausems(DELAY_MS);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
