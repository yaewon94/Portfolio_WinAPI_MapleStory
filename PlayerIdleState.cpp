#include "PCH.h"
#include "PlayerIdleState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// ������
PlayerIdleState::PlayerIdleState() : State(OBJECT_STATE::IDLE)
{
}

// �Ҹ���
PlayerIdleState::~PlayerIdleState()
{
}

// ���� ����
void PlayerIdleState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::IDLE);
}