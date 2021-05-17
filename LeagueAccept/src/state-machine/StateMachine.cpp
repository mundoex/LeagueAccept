#include "StateMachine.h"

StateMachine::StateMachine()
{
	this->currentState = nullptr;
	this->states = std::map<State, BaseState*>();
}

StateMachine::~StateMachine()
{

}

void StateMachine::Update(float deltaTime)
{
	currentState->Update(deltaTime);
}

void StateMachine::Render()
{
	currentState->Render();
}

void StateMachine::Change(State newState, void* params)
{
	BaseState* possibleNewState = states.at(newState);
	if (possibleNewState!=nullptr) {
		currentState = possibleNewState;
		currentState->Enter(params);
	}
	else {
		throw "No state found";
	}
}

void StateMachine::InsertStatePair(State stateEnum, BaseState* state)
{
	this->states.insert(std::pair(stateEnum, state));
}
