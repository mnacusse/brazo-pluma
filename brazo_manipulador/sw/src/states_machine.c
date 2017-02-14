#include "../inc/states_machine.h"

void cambiarEngState(BrazoState *state,engine_states *es)
{
	if (state->en_state == es || state->en_state == WAITING || es == WAITING)
	{
		state->en_state = es;
		
	}
}


void cambiarManipState(BrazoState *state,manip_states *ms)
{
	if (state->m_state == ms || state->en_state == WAITING)
		state->m_state = ms;
}


void getMsg(char *msg, BrazoState * state);
{
	msg = state->msg;
}


