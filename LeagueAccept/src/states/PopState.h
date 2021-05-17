#pragma once
#include "../opencv-utils/MouseWrapper.h"
#include "BaseState.h"

class PopState : public BaseState{
private:
	MouseWrapper mouse;
	POINT point;
public:
	PopState(StateMachine* stateMachine, HMENU hMenu) : BaseState(stateMachine, hMenu) 
	{ 
		this->mouse = MouseWrapper();
	};
	~PopState();
	void Enter(void* params) override;
	void Update(float deltaTime) override;
};