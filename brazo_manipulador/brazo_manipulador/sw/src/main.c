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

#include "../sw/inc/main.h"
#include "board.h"
#include "stdint.h"
#include "inttypes.h"
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "../../hw/inc/hw_handler.h"
#include "../../sw/inc/states_machine.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

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

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 500); // cada cuantos tics de reloj tiene que generar la interrupcion. EN este caso cada un ms
	/* Usa la base de tiempo del procesador (con el contador de 24 bits),
	 * es decir, cuenta 200M / 1000 en este caso, y ahi te queda 1ms
	 * */
	incializarPuertos(void);
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
	BrazoState maquina = {.en_state = WAITING, .m_state = MANIPULATOR_FREE, .distance = 0, .msg=''};
	char str[20];
	int32_t led,cont = 0;
	uint8_t butStat = 0x00;
	initHardware();
	pausems(100);
	led = LED;
	str = "Sistema inicializado ... ";
	showState(&maquina);
	while (1)
	{
		engine_states engState_prev = maquina->en_state;
		manip_states manipState_prev = maquina->m_state;
		butStat = Button_GetStatus();
		switch(butStat)
		{
			case BUTTONS_STOP:
				cambiarEngState(&maquina,WAITING);
				break;
			case BUTTONS_UP:
				cambiarEngState(&maquina,ENGINE_UP);
				break;
			case BUTTONS_DOWN:
				cambiarEngState(&maquina,ENGINE_DOWN);
				break;
			case BUTTONS_EN_AIR:
				cambiarManipState(&maquina,MANIPULATOR_HOLDING);
				break;
			case BUTTONS_DIS_AIR:
				cambiarManipState(&maquina,MANIPULATOR_FREE);
				break;
		}
		if (engState_prev |= maquina->en_state || manipState_prev |= maquina->m_state )
			showState(&maquina);
		/*sprintf(str,"asda: %"PRIu32"-->\r\n ",butStat);
		DEBUGSTR(str);
		sprintf(str,"Evento nro: %"PRIu32"\r\n",cont);
		cont++;
		DEBUGSTR(str);

		Board_LED_Toggle(LED);*/
		pausems(DELAY_MS);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
