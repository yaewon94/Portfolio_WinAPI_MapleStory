#include "PCH.h"
#include "MonsterIdleState.h"
#include "FSM.h"
#include "Monster.h"

// 생성자
MonsterIdleState::MonsterIdleState() : me(nullptr)
{
}

// 소멸자
MonsterIdleState::~MonsterIdleState()
{
	me = nullptr;
}

// 초기화
void MonsterIdleState::Init()
{
	me = (Monster*)GetFsm().GetOwner();
}

// 상태 진입
void MonsterIdleState::Enter()
{
	IdleState::Enter();
}

// 매 프레임마다 호출
void MonsterIdleState::Stay()
{
	// 범위 내에 플레이어가 감지되면, 추적 상태로 전환
	if (me->DetectPlayer()) GetFsm().ChangeState(OBJECT_STATE::TRACE);
}