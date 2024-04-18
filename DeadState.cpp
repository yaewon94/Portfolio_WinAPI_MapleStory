#include "PCH.h"
#include "DeadState.h"
#include "FSM.h"
#include "Collider.h"
#include "GameObject.h"

// ������
DeadState::DeadState(float Duration) : State(OBJECT_STATE::DEAD, 0.f, Duration)
{
}

// ���� ������
DeadState::DeadState(const DeadState& origin) : State(origin)
{
}

// �Ҹ���
DeadState::~DeadState()
{
}

// ���� ����
void DeadState::Enter()
{
	// �ݶ��̴� ��Ȱ��ȭ
	Collider* collider =GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(false);
}

// ���� ����
void DeadState::Exit()
{
	// �ݶ��̴� Ȱ��ȭ
	Collider* collider = GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(true);
}