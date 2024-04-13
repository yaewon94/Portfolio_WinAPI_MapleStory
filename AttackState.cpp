#include "PCH.h"
#include "AttackState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
AttackState::AttackState() : State(OBJECT_STATE::ATTACK)
{
}

// 소멸자
AttackState::~AttackState()
{
}

// 상태 진입
void AttackState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::ATTACK);
}

// 상태 해제
void AttackState::Exit()
{
}