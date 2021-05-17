#include "BaseState.h"

BaseState::BaseState()
{

}
//dependency injection
BaseState::BaseState(StateMachine* stateMachine, HMENU hMenu)
{
	this->stateMachine = stateMachine;
	this->hMenu = hMenu;
}

BaseState::~BaseState()
{
}
