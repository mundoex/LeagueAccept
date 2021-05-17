#pragma once
#include "../ApplicationConstants.h"
#include "BaseState.h"

class IdleState : public BaseState
{
public:
	IdleState(StateMachine* stateMachine, HMENU hMenu) : BaseState(stateMachine, hMenu){}
	~IdleState();
	void Render() override;
};