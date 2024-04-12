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
	ChangeState(OBJECT_STATE::IDLE);
}

// 상태 추가
void FSM::AddState(State& state)
{
	if (FindState(state.type) == nullptr)
	{
		state.fsm = this;
		stateMap.insert(make_pair(state.type, &state));
	}
	else Log(LOG_TYPE::LOG_ERROR, L"이미 추가된 상태입니다");
}

// 상태 변경
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
		Log(LOG_TYPE::LOG_ERROR, L"변경하려는 상태가 없습니다");
	}
}

// 상태 찾기
State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}