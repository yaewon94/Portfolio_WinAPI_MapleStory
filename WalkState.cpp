#include "PCH.h"
#include "WalkState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
WalkState::WalkState() : State(OBJECT_STATE::WALK)
{
}

// 소멸자
WalkState::~WalkState()
{
}

// 상태 진입
void WalkState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::WALK);
}