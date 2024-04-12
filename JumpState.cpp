#include "PCH.h"
#include "JumpState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
JumpState::JumpState() : State(OBJECT_STATE::JUMP)
{
}

// 소멸자
JumpState::~JumpState()
{
}

// 상태 진입
void JumpState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::JUMP);
}