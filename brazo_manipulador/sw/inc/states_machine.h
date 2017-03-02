#define _GNU_SOURCE
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../../hw/inc/hw_handler.h"
typedef enum engine_states {WAITING, ENGINE_UP,ENGINE_DOWN, ENGINE_ERROR} engine_states;
typedef enum manip_states {MANIPULATOR_FREE, MANIPULATOR_HOLDING, MANIP_ERROR} manip_states;

typedef struct {
  engine_states en_state;
  manip_states m_state;
  uint16_t distance;
  char msg[64];
} BrazoState;

void cambiarEngState(BrazoState *state,engine_states *es);
void cambiarManipState(BrazoState *state,manip_states *ms);
void showState(BrazoState *state);
void getMsg(char *msg);

