#include "PCH.h"
#include "State.h"

// ������
State::State(OBJECT_STATE type, float coolDown) : type(type), CoolDown(coolDown), fsm(nullptr)
{
	// fsm �ʱ�ȭ�� FSM::AddState()���� ���
}

// �Ҹ���
State::~State()
{
	fsm = nullptr;
}