#include "PCH.h"
#include "DeadBeforeState.h"
#include "Collider.h"
#include "FSM.h"
#include "GameObject.h"

// ������
DeadBeforeState::DeadBeforeState(float Duration) 
	: State(OBJECT_STATE::DEAD_BEFORE, OBJECT_STATE::DEAD, 0.f, Duration)
{
}

// ���� ������
DeadBeforeState::DeadBeforeState(const DeadBeforeState& origin) : State(origin)
{
}

// �Ҹ���
DeadBeforeState::~DeadBeforeState()
{
}

// ���� ����
void DeadBeforeState::Enter()
{
	// �ݶ��̴� ��Ȱ��ȭ
	Collider* collider = GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(false);
}