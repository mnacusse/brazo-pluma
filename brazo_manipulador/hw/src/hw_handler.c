#include "../inc/hw_handler.h"
#define MD_PUP						(0x0 << 3)		/** Enable pull-up resistor at pad */
#define MD_BUK						(0x1 << 3)		/** Enable pull-down and pull-up resistor at resistor at pad (repeater mode) */
#define MD_PLN						(0x2 << 3)		/** Disable pull-down and pull-up resistor at resistor at pad */
#define MD_PDN						(0x3 << 3)		/** Enable pull-down resistor at pad */
#define MD_EHS						(0x1 << 5)		/** Enable fast slew rate */
#define MD_EZI						(0x1 << 6)		/** Input buffer enable */
#define MD_ZI						(0x1 << 7)		/** Disable input glitch filter */
#define MD_EHD0						(0x1 << 8)		/** EHD driver strength low bit */
#define MD_EHD1						(0x1 << 8)		/** EHD driver strength high bit */
#define MD_PLN_FAST					(MD_PLN | MD_EZI | MD_ZI | MD_EHS)

void incializarPuertos(void)
{
	// Ports initialization
	Chip_SCU_PinMux(MUP_IN_PIN,MUP_IN_PORT,MD_PUP|MD_EZI|MD_ZI,MUP_IN_FUNC); /* */
	Chip_SCU_PinMux(MUP_OUT_PIN,MUP_OUT_PORT,MD_PUP|MD_EZI|MD_ZI,MUP_OUT_FUNC); /* */
	Chip_SCU_PinMux(MDOWN_IN_PIN,MDOWN_IN_PORT,MD_PUP|MD_EZI|MD_ZI,MDOWN_IN_FUNC); /* */
	Chip_SCU_PinMux(MDOWN_OUT_PIN,MDOWN_OUT_PORT,MD_PUP|MD_EZI|MD_ZI,MDOWN_OUT_FUNC); /* */
	Chip_SCU_PinMux(MANIP_IN_PIN,MANIP_IN_PORT,MD_PUP|MD_EZI|MD_ZI,MANIP_IN_FUNC); /* */
	Chip_SCU_PinMux(MANIP_OUT_PIN,MANIP_OUT_PORT,MD_PUP|MD_EZI|MD_ZI,MANIP_OUT_FUNC); /* */
	Chip_SCU_PinMux(MSTOP_IN_PIN,MSTOP_IN_PORT,MD_PUP|MD_EZI|MD_ZI,MSTOP_IN_FUNC); /* */

	//Ports configuration
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MUP_IN_GPION,(1<<MUP_IN_GPIOP),0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MUP_OUT_GPION,(1<<MUP_OUT_GPIOP),1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MDOWN_IN_GPION,(1<<MDOWN_IN_GPIOP),0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MDOWN_OUT_GPION,(1<<MDOWN_OUT_GPIOP),1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MANIP_IN_GPION,(1<<MANIP_IN_GPIOP),0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MANIP_OUT_GPION,(1<<MANIP_OUT_GPIOP),1);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, MSTOP_IN_GPION,(1<<MSTOP_IN_GPIOP),0);
	// output Port sets to zero
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 0);
	// input ports set to zero
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_IN_GPION,MUP_IN_GPIOP, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_IN_GPION,MDOWN_IN_GPIOP, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MSTOP_IN_GPION,MSTOP_IN_GPIOP, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_IN_GPION,MANIP_IN_GPIOP, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 1);


}


uint8_t loadCable(){

	uint8_t res = 0x0;
	char str[64];
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
	//sprintf(str,"Subiendo el cable ... \r\n ");
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 1);
	DEBUGSTR(str);
	return res;
}

uint8_t releaseCable()
{
	uint8_t res = 0x0;
	char str[64];
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
	sprintf(str,"Bajando el cable ... \r\n ");
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 1);
	DEBUGSTR(str);
	return res;
}

uint8_t stopMotor()
{
	uint8_t res = 0x0;
	char str[64];
	//sprintf(str,"Motor detenido\r\n ");
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
	DEBUGSTR(str);
	return res;
}

uint8_t enableAir()
{
	uint8_t ret = 0x0;
	char str[64];
	sprintf(str,"Aire habilitado .... \r\n ");
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 1);
	DEBUGSTR(str);
	return ret;
}

uint8_t disableAir()
{
	uint8_t ret = 0x0;
	char str[64];
	sprintf(str,"Aire desabilitado .... \r\n ");
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MANIP_OUT_GPION,MANIP_OUT_GPIOP, 0);
	DEBUGSTR(str);
	return ret;
}


uint8_t Button_GetStatus(void)
{
	//char str[64];


	uint8_t ret = NO_BUTTON_PRESSED;
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MUP_IN_GPION , (1<<MUP_IN_GPIOP)) == 0) {
		ret |= BUTTONS_UP;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MDOWN_IN_GPION , (1<<MDOWN_IN_GPIOP)) == 0) {
		ret |= BUTTONS_DOWN;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MSTOP_IN_GPION , (1<<MSTOP_IN_GPIOP)) == 0) {
		ret |= BUTTONS_STOP;
	}
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MANIP_IN_GPION , (1<<MANIP_IN_GPIOP)) == 0) {
		ret |= BUTTONS_DIS_AIR;
	}
	//sprintf(str,"termino de ver los botones .... \r\n ");
	//DEBUGSTR(str);
	return ret;
}
