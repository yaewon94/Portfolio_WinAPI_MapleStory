#include "PCH.h"
#include "State.h"

// ������
State::State(OBJECT_STATE type) : type(type), fsm(nullptr)
{
	// fsm �ʱ�ȭ�� FSM::AddState()���� ���
}

// �Ҹ���
State::~State()
{
	fsm = nullptr;
}