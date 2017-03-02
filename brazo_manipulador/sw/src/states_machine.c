#include "../inc/states_machine.h"

void cambiarEngState(BrazoState *state,engine_states *es)
{
	if (state->en_state == es || state->en_state == WAITING || es == WAITING)
	{
		state->en_state = es;
		switch(es)
		{
			case MANIPULATOR_FREE:
				disableAir();
				state->msg = "Manipulador liberado ... \r\n";
				break;
			case MANIPULATOR_HOLDING:
				enableAir();
				state->msg = "aire habilitado ... \r\n";
				break;
			default:
				enableAir();
				state->msg = "aire habilitado por defecto... \r\n";
		}
	}
}


void cambiarManipState(BrazoState *state,manip_states *ms)
{
	if (state->m_state == ms || state->en_state == WAITING)
	{
		state->m_state = ms;
		switch(ms)
		{
		case ENGINE_UP:
			loadCable();
			state->msg = "cargando el cable ... \r\n";
			break;
		case ENGINE_DOWN:
			releaseCable();
			state->msg = "bajando el cable ... \r\n";
			break;
		default:
			stopMotor();
			state->msg = "motor detenido... \r\n";
		}
	}
}

void showState(BrazoState *state)
{
	char str[64];
	char m_state[20];
	char en_state[20];
	switch (state->en_state)
	{
	case WAITING:
		en_state = "detenido \r\n";
		break;
	case ENGINE_UP:
		en_state = "subiendo \r\n";
		break;
	case ENGINE_DOWN:
		en_state = "bajando \r\n";
		break;
	}
	switch (state->m_state)
		{
		case MANIPULATOR_FREE:
			m_state = "liberado \r\n";
			break;
		case MANIPULATOR_HOLDING:
			m_state = "sosteniendo placa \r\n";
			break;
		}
	sprintf(str,"Estado del sistema:\r\n Motor:");
	DEBUGSTR(str);
	DEBUGSTR(en_state);
	sprintf(str,"Manipulador: ");
	DEBUGSTR(str);
	DEBUGSTR(m_state);
}


void getMsg(char *msg, BrazoState * state);
{
	msg = state->msg;
}


