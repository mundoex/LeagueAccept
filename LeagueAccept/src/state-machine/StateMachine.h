#pragma once
#include <map>
#include "../states/State.h"
class BaseState;	//to prevent circular includes
#include "../states/BaseState.h"

class StateMachine {
	private:
		BaseState* currentState;
		std::map<State, BaseState*> states;
	public:
		StateMachine();
		~StateMachine();
		void Update(float deltaTime);
		void Render();
		void Change(State newState, void* params=nullptr);
		void InsertStatePair(State stateEnum, BaseState* state);
};