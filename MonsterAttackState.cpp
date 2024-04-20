#include "PCH.h"
#include "MonsterAttackState.h"
#include "FSM.h"
#include "Monster.h"
#include "TimeManager.h"

// 생성자
MonsterAttackState::MonsterAttackState(float coolDown) 
	: State(OBJECT_STATE::ATTACK, coolDown), me(nullptr)
{
}

// 복사 생성자
MonsterAttackState::MonsterAttackState(const MonsterAttackState& origin) : State(origin), me(nullptr)
{
}

// 소멸자
MonsterAttackState::~MonsterAttackState()
{
	me = nullptr;
}

// 초기화
void MonsterAttackState::Init()
{
	State::Init();
	me = (Monster*)GetFsm().GetOwner();
}

// 상태 진입
void MonsterAttackState::Enter()
{
	me->Attack();
}

// 상태 종료
void MonsterAttackState::Exit()
{
	exitTime = TimeManager::GetInstance().GetSecond();
}