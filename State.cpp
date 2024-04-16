#include "PCH.h"
#include "State.h"

// ������
State::State(OBJECT_STATE type, float coolDown) : type(type), CoolDown(coolDown), fsm(nullptr)
{
	// fsm �ʱ�ȭ�� FSM::AddState()���� ���
}

// ���� ������
State::State(const State& origin) : type(origin.type), CoolDown(origin.CoolDown), fsm(nullptr)
{
	// FSM�� ���� �����ڿ��� fsm �ʱ�ȭ
}

// �Ҹ���
State::~State()
{
	fsm = nullptr;
}