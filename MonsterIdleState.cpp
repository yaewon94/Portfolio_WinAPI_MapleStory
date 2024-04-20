#include "PCH.h"
#include "MonsterIdleState.h"
#include "FSM.h"
#include "Monster.h"

// 생성자
MonsterIdleState::MonsterIdleState() : State(OBJECT_STATE::IDLE), me(nullptr)
{
}

// 복사 생성자
MonsterIdleState::MonsterIdleState(const MonsterIdleState& origin) : State(origin), me(nullptr)
{
	// 복사생성자 호출시점엔 owner가 nullptr라 me는 나중에 초기화 해줘야 함
	// TODO : Init() 호출 안하는 객체 있는지 체크
}

// 소멸자
MonsterIdleState::~MonsterIdleState()
{
	me = nullptr;
}

// 초기화
void MonsterIdleState::Init()
{
	State::Init();
	me = (Monster*)GetFsm().GetOwner();
}

// 매 프레임마다 호출
void MonsterIdleState::Stay()
{
	// 범위 내에 플레이어가 감지되면, 추적 상태로 전환
	if (me->DetectPlayer()) GetFsm().ChangeState(OBJECT_STATE::TRACE);
	// 감지되지 않으면 공격상태 전환
	else GetFsm().ChangeState(OBJECT_STATE::ATTACK);
}