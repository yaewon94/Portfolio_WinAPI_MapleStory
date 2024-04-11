#include "PCH.h"
#include "State.h"

// 생성자
State::State(OBJECT_STATE type) : type(type), fsm(nullptr)
{
	// fsm 초기화는 FSM::AddState()에서 담당
}

// 소멸자
State::~State()
{
	fsm = nullptr;
}