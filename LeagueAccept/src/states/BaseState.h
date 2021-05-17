#pragma once
#include <windows.h>
#include "../ApplicationConstants.h"
class StateMachine;	//to prevent circular includes
#include "../state-machine/StateMachine.h"

class BaseState
{
	protected:
		StateMachine* stateMachine;
		HMENU hMenu;

	public:
		BaseState();
		BaseState(StateMachine* stateMachine, HMENU hMenu);
		~BaseState();
		virtual void Enter(void* params) { 
			//do nothing
		}
		virtual void Update(float deltaTime) {
			//do nothing
		}
		virtual void Render() {
			//do nothing
		};
};