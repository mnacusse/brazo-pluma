#define _GNU_SOURCE
#include <stdint.h>
#include <string.h>
#include <stdio.h>


#define MUP_IN_PIN 		0x04
#define MUP_IN_PORT 	0x00
#define MUP_IN_FUNC 	FUNC0
#define MUP_IN_GPION 	0x02
#define MUP_IN_GPIOP 	0x00

#define MUP_OUT_PIN 	0x04
#define MUP_OUT_PORT	0x04
#define MUP_OUT_FUNC 	FUNC0
#define MUP_OUT_GPION	0x02
#define MUP_OUT_GPIOP	0x04

#define MDOWN_IN_PIN 	0x04
#define MDOWN_IN_PORT 	0x01
#define MDOWN_IN_FUNC 	FUNC0
#define MDOWN_IN_GPION	0x02
#define MDOWN_IN_GPIOP	0x01

#define MDOWN_OUT_PIN 	0x04
#define MDOWN_OUT_PORT 	0x06
#define MDOWN_OUT_FUNC 	0x0FUNC0
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

void incializarPuertos(void);

uint16_t loadCable();
uint16_t releaseCable();
uint16_t stopMotor();

uint16_t enableAir();
uint16_t disableAir();
