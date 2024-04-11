#include "PCH.h"
#include "PlayerIdleState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
PlayerIdleState::PlayerIdleState() : State(OBJECT_STATE::IDLE)
{
}

// 소멸자
PlayerIdleState::~PlayerIdleState()
{
}

// 상태 진입
void PlayerIdleState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::IDLE);
}