#define _GNU_SOURCE
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "board.h"


#define MUP_IN_PIN 		0x04
#define MUP_IN_PORT 	0x00
#define MUP_IN_FUNC 	FUNC0
#define MUP_IN_GPION 	0x02
#define MUP_IN_GPIOP 	0x00

#define MUP_OUT_PIN 	0x01
#define MUP_OUT_PORT	0x05
#define MUP_OUT_FUNC 	FUNC0
#define MUP_OUT_GPION	0x01
#define MUP_OUT_GPIOP	0x08

#define MDOWN_IN_PIN 	0x04
#define MDOWN_IN_PORT 	0x01
#define MDOWN_IN_FUNC 	FUNC0
#define MDOWN_IN_GPION	0x02
#define MDOWN_IN_GPIOP	0x01

#define MDOWN_OUT_PIN 	0x04
#define MDOWN_OUT_PORT 	0x06
#define MDOWN_OUT_FUNC 	FUNC0
#define MDOWN_OUT_GPION	0x02
#define MDOWN_OUT_GPIOP	0x06

#define MANIP_IN_PIN 	0x04
#define MANIP_IN_PORT 	0x02
#define MANIP_IN_FUNC 	FUNC0
#define MANIP_IN_GPION	0x02
#define MANIP_IN_GPIOP	0x02

#define MANIP_OUT_PIN 	0x04
#define MANIP_OUT_PORT 	0x05
#define MANIP_OUT_FUNC 	FUNC0
#define MANIP_OUT_GPION	0x02
#define MANIP_OUT_GPIOP	0x05

#define MSTOP_IN_PIN 	0x04
#define MSTOP_IN_PORT 	0x03
#define MSTOP_IN_FUNC 	FUNC0
#define MSTOP_IN_GPION 	0x02
#define MSTOP_IN_GPIOP 	0x03

#define NO_BUTTON_PRESSED 0x00
#define BUTTONS_STOP	0X01
#define BUTTONS_UP		0X02
#define BUTTONS_DOWN	0X04
#define BUTTONS_EN_AIR	0X08
#define BUTTONS_DIS_AIR 0x16


void incializarPuertos(void);

uint8_t loadCable();
uint8_t releaseCable();
uint8_t stopMotor();

uint8_t enableAir();
uint8_t disableAir();
uint8_t Button_GetStatus();
