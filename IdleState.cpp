#include "PCH.h"
#include "IdleState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
IdleState::IdleState() : State(OBJECT_STATE::IDLE)
{
}

// 소멸자
IdleState::~IdleState()
{
}

// 상태 진입
void IdleState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::IDLE);
}