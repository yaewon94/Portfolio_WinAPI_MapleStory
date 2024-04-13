#include "PCH.h"
#include "AttackState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// ������
AttackState::AttackState() : State(OBJECT_STATE::ATTACK)
{
}

// �Ҹ���
AttackState::~AttackState()
{
}

// ���� ����
void AttackState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::ATTACK);
}

// ���� ����
void AttackState::Exit()
{
}