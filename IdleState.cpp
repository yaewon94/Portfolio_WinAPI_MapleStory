#include "PCH.h"
#include "IdleState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// ������
IdleState::IdleState() : State(OBJECT_STATE::IDLE)
{
}

// �Ҹ���
IdleState::~IdleState()
{
}

// ���� ����
void IdleState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::IDLE);
}