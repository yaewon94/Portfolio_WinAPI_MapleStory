#include "PCH.h"
#include "JumpState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// ������
JumpState::JumpState() : State(OBJECT_STATE::JUMP)
{
}

// �Ҹ���
JumpState::~JumpState()
{
}

// ���� ����
void JumpState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::JUMP);
}