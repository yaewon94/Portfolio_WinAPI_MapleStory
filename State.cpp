#include "PCH.h"
#include "State.h"

// ������
State::State(FSM& fsm, OBJECT_STATE type) : fsm(&fsm), type(type)
{
}

// �Ҹ���
State::~State()
{
	fsm = nullptr;
}