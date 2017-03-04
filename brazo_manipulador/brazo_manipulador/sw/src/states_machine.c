#include "../inc/states_machine.h"

void cambiarEngState(BrazoState *state,engine_states es)
{
	if (state->en_state == es || state->en_state == WAITING || es == WAITING)
	{
		state->en_state = es;
		switch(es)
		{
			case MANIPULATOR_FREE:
				disableAir();
	//			state->msg = "Manipulador liberado ... \r\n";
				break;
			case MANIPULATOR_HOLDING:
				enableAir();
		//		state->msg = "aire habilitado ... \r\n";
				break;
			default:
				enableAir();
			//	state->msg = "aire habilitado por defecto... \r\n";
		}
	}
}


void cambiarManipState(BrazoState *state,manip_states ms)
{
	if (state->m_state == ms || state->en_state == WAITING)
	{
		state->m_state = ms;
		switch(ms)
		{
		case ENGINE_UP:
			loadCable();
			//state->msg = "cargando el cable ... \r\n";
			break;
		case ENGINE_DOWN:
			releaseCable();
			//state->msg = "bajando el cable ... \r\n";
			break;
		default:
			stopMotor();
			//state->msg = "motor detenido... \r\n";
		}
	}
}

void showState(BrazoState *state)
{
	uint8_t str[64];
	sprintf(str,"Estado del sistema:\r\n Motor:");
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


