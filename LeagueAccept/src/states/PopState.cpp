#include "PopState.h"

PopState::~PopState()
{
	
}

void PopState::Enter(void* params)
{
	this->point = *(POINT*)params;
}

void PopState::Update(float deltaTime)
{
	this->mouse.moveTo(this->point);
	this->mouse.click();
	this->stateMachine->Change(State::WAITING_FOR_POP);
}