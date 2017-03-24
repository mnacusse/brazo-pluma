#include "../inc/states_machine.h"

void cambiarManipState(BrazoState *state,manip_states ms)
{
	switch(ms)
	{
		case MANIPULATOR_FREE:
			if(state->en_state == WAITING)
			{
				disableAir();
				state->m_state = ms;
			}
			break;
		case MANIPULATOR_HOLDING:
			enableAir();
			state->m_state = ms;
			break;
		default:
			enableAir();
	}
}


void cambiarEngState(BrazoState *state,engine_states es)
{
	uint8_t str[64];
		state->en_state = es;
		switch(es)
		{
		case ENGINE_UP:
			loadCable();
			break;
		case ENGINE_DOWN:
			releaseCable();
			break;
		case WAITING:
			stopMotor();
			break;
		default:
			stopMotor();
		}
}

void showState(BrazoState *state)
{
	uint8_t str[64];
	sprintf(str,"Estado del sistema:\r\n");
	DEBUGSTR(str);
	switch (state->en_state)
	{
	case WAITING:
		sprintf(str,"Motor: detenido\r\n");
		DEBUGSTR(str);
		break;
	case ENGINE_UP:
		sprintf(str,"Motor: subiendo\r\n");
		DEBUGSTR(str);
		break;
	case ENGINE_DOWN:
		sprintf(str,"Motor: bajando\r\n");
		DEBUGSTR(str);
		break;
	}
	sprintf(str,"Manipulador: ");
	DEBUGSTR(str);
	switch (state->m_state)
	{
		case MANIPULATOR_FREE:
			sprintf(str,"liberado\r\n");
			DEBUGSTR(str);
			break;
		case MANIPULATOR_HOLDING:
			sprintf(str,"sosteniendo placa \r\n");
			DEBUGSTR(str);
			break;
	}
}


void getMsg(char *msg, BrazoState * state)
{
	*msg = *state->msg;
}


