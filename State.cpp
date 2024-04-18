#include "PCH.h"
#include "State.h"
#include "FSM.h"
#include "TimeManager.h"

// ������
State::State(OBJECT_STATE type, float coolDown, float Duration) 
	: type(type), CoolDown(coolDown), Duration(Duration), fsm(nullptr)
{
	// fsm �ʱ�ȭ�� FSM::AddState()���� ���
}

// ���� ������
State::State(const State& origin) 
	: type(origin.type), CoolDown(origin.CoolDown), Duration(origin.Duration)
	, fsm(nullptr)
{
	// FSM�� ���� �����ڿ��� fsm �ʱ�ȭ
}

// �Ҹ���
State::~State()
{
	fsm = nullptr;
}

// �� �����Ӹ��� ȣ��
void State::Stay()
{
	// ���� ���ӽð��� ������ ��쿡��, ����ð� ����
	if (Duration > 0.f)
	{
		time = TimeManager::GetInstance().GetDeltaTime();

		// ���ӽð��� �ʰ��� ���, ����Ʈ ���·� ��ȯ
		if (time >= Duration) fsm->ChangeState(fsm->GetDefaultState());
	}
}