#include "PCH.h"
#include "FSM.h"
#include "State.h"

// 생성자
FSM::FSM(GameObject& owner) : Component(owner), curState(nullptr)
{
}

// 복사 생성자
FSM::FSM(const FSM& origin) : Component(origin), curState(nullptr)
{
}

// 소멸자
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

// 초기화
void FSM::Init()
{
	// IDLE 상태를 디폴트로 함
	curState = stateMap.find(OBJECT_STATE::IDLE)->second;
	curState->Enter();
}