#include "PCH.h"
#include "MonsterTraceState.h"
#include "Animator.h"
#include "FSM.h"
#include "Monster.h"
#include "TimeManager.h"

// 생성자
MonsterTraceState::MonsterTraceState() : State(OBJECT_STATE::TRACE, 5), me(nullptr)
{
}

// 소멸자
MonsterTraceState::~MonsterTraceState()
{
	me = nullptr;
}

// 초기화
void MonsterTraceState::Init()
{
	me = (Monster*)GetFsm().GetOwner();
}

// 상태 진입
void MonsterTraceState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::TRACE);
}

// 매 프레임마다 호출
void MonsterTraceState::Stay()
{
	// 범위 내에 플레이어가 있을 경우, 플레이어 추격
	if (me->DetectPlayer())
	{
		if (me->Trace()) return;
	}

	// 범위 내에 플레이어가 없거나, 플레이어 추격이 끝난 경우
	// IDLE 상태로 전환
	GetFsm().ChangeState(OBJECT_STATE::IDLE);
}

// 상태 종료
void MonsterTraceState::Exit()
{
	exitTime = TimeManager::GetInstance().GetSecond();
}