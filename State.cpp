#include "PCH.h"
#include "State.h"

// 持失切
State::State(FSM& fsm, OBJECT_STATE type) : fsm(&fsm), type(type)
{
}

// 社瑚切
State::~State()
{
	fsm = nullptr;
}