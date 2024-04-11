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
	curState = stateMap.find(OBJECT_STATE::IDLE)->second;
	curState->Enter();
}