#include "PCH.h"
#include "FSM.h"
#include "Animator.h"
#include "GameObject.h"
#include "State.h"
#include "TimeManager.h"

// ������
FSM::FSM(GameObject& owner) 
	: Component(owner), curState(nullptr)
{
}

// ���� ������
FSM::FSM(const FSM& origin) 
	: Component(origin), DefaultStateType(origin.DefaultStateType)
	, curStateType(origin.DefaultStateType), curState(nullptr)
{
	for (auto& pair : origin.stateMap)
	{
		State* state = pair.second->Clone();
		state->SetFsm(*this);
		stateMap.insert(make_pair(pair.first, state));
	}
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
	// ���� Init()
	for (auto& state : stateMap)
	{
		state.second->Init();
	}

	// ����Ʈ ���� ��ȯ
	ChangeState(DefaultStateType);
}

// �� �����Ӹ��� ȣ��
void FSM::FinalTick()
{
	if(curState != nullptr) curState->Stay();
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
	if (curState != nullptr && curState->type == type)
	{
		Log(LOG_TYPE::LOG_ERROR, L"���� ���¿� �����Ϸ��� ���°� �����ϴ�");
		return;
	}

	// ���� ��ü ã��
	auto state = FindState(type);

	// ��ü�� ������ ���
	if (state != nullptr)
	{
		// ��Ÿ�� üũ
		if ((int)(TimeManager::GetInstance().GetSecond() - state->exitTime) < state->CoolDown)
		{
			Log(LOG_TYPE::LOG_ERROR, L"���� �ش� ���·� ������ �� �����ϴ�");
			return;
		}

		// ���� ����
		if(curState != nullptr) curState->Exit();
		curState = state;
		curStateType = type;
		curState->Enter();
		GetOwner()->GetComponent<Animator>()->ChangeAnimation(type);
	}
	// ��ü�� �������� ���� ���
	// ���� ��ü�� ������ �ִϸ��̼� ��ȯ �뵵
	else
	{
		// ���� ���°� �ִ� ��� ����
		if (curState != nullptr) curState->Exit();
		curState = nullptr;
		GetOwner()->GetComponent<Animator>()->ChangeAnimation(type);
		curStateType = type;
	}
}

// ���� ã��
State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}