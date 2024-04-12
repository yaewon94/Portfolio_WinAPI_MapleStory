#include "PCH.h"
#include "FSM.h"
#include "State.h"

// ������
FSM::FSM(GameObject& owner) : Component(owner), curState(nullptr)
{
}

// ���� ������
FSM::FSM(const FSM& origin) : Component(origin), curState(nullptr)
{
}

// �Ҹ���
FSM::~FSM()
{
	curState = nullptr;

	for (auto& state : stateMap)
	{
		if (state.second != nullptr)
		{
			delete state.second;
			nullptr;
		}
	}
}

// �ʱ�ȭ
void FSM::Init()
{
	// IDLE ���¸� ����Ʈ�� ��
	ChangeState(OBJECT_STATE::IDLE);
}

// ���� �߰�
void FSM::AddState(State& state)
{
	if (FindState(state.type) == nullptr)
	{
		state.fsm = this;
		stateMap.insert(make_pair(state.type, &state));
	}
	else Log(LOG_TYPE::LOG_ERROR, L"�̹� �߰��� �����Դϴ�");
}

// ���� ����
void FSM::ChangeState(OBJECT_STATE type)
{
	auto state = FindState(type);

	if (state != nullptr)
	{
		if (curState != nullptr) curState->Exit();
		curState = state;
		curState->Enter();
	}
	else
	{
		Log(LOG_TYPE::LOG_ERROR, L"�����Ϸ��� ���°� �����ϴ�");
	}
}

// ���� ã��
State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}