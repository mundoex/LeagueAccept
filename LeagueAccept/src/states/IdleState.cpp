#include "IdleState.h"

IdleState::~IdleState()
{
}

void IdleState::Render()
{
	ModifyMenu(this->hMenu, IDR_STOP, MF_BYCOMMAND | MF_STRING, IDR_START, "Start");
}