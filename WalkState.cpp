#include "PCH.h"
#include "WalkState.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"

// ������
WalkState::WalkState() : State(OBJECT_STATE::WALK)
{
}

// �Ҹ���
WalkState::~WalkState()
{
}

// ���� ����
void WalkState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::WALK);
}