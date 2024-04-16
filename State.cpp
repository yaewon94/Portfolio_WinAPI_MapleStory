#include "PCH.h"
#include "State.h"

// 생성자
State::State(OBJECT_STATE type, float coolDown) : type(type), CoolDown(coolDown), fsm(nullptr)
{
	// fsm 초기화는 FSM::AddState()에서 담당
}

// 복사 생성자
State::State(const State& origin) : type(origin.type), CoolDown(origin.CoolDown), fsm(nullptr)
{
	// FSM의 복사 생성자에서 fsm 초기화
}

// 소멸자
State::~State()
{
	fsm = nullptr;
}