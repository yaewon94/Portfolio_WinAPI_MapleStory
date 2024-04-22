#include "PCH.h"
#include "State.h"
#include "FSM.h"
#include "TimeManager.h"

// 생성자
State::State(OBJECT_STATE type, float coolDown, float Duration) 
	: type(type), CoolDown(coolDown), Duration(Duration), fsm(nullptr)
{
	// fsm 초기화는 FSM::AddState()에서 담당
}

State::State(OBJECT_STATE type, OBJECT_STATE nextState, float coolDown, float Duration) 
	: type(type), nextState(nextState), CoolDown(coolDown), Duration(Duration), fsm(nullptr)
{
	// fsm 초기화는 FSM::AddState()에서 담당
}

// 복사 생성자
State::State(const State& origin) 
	: type(origin.type), CoolDown(origin.CoolDown), Duration(origin.Duration)
	, fsm(nullptr)
{
	// FSM의 복사 생성자에서 fsm 초기화
}

// 소멸자
State::~State()
{
	fsm = nullptr;
}

// 초기화
void State::Init()
{
	if(nextState == OBJECT_STATE::NONE) nextState = GetFsm().GetDefaultState();
}

// 매 프레임마다 호출
void State::Stay()
{
	// 상태 지속시간이 존재할 경우에만, 경과시간 누적
	if (Duration > 0.f)
	{
		time += TimeManager::GetInstance().GetDeltaTime();
	}

	// 지속시간을 초과한 경우, 다음 상태로 전환
	if (time >= Duration)
	{
		time = 0.f;
		fsm->ChangeState(nextState);
	}
}