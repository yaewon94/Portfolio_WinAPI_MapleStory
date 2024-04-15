#include "PCH.h"
#include "MonsterTraceState.h"
#include "Animator.h"
#include "FSM.h"
#include "Monster.h"
#include "TimeManager.h"

// ������
MonsterTraceState::MonsterTraceState() : State(OBJECT_STATE::TRACE, 5), me(nullptr)
{
}

// �Ҹ���
MonsterTraceState::~MonsterTraceState()
{
	me = nullptr;
}

// �ʱ�ȭ
void MonsterTraceState::Init()
{
	me = (Monster*)GetFsm().GetOwner();
}

// ���� ����
void MonsterTraceState::Enter()
{
	GetFsm().GetOwner()->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::TRACE);
}

// �� �����Ӹ��� ȣ��
void MonsterTraceState::Stay()
{
	// ���� ���� �÷��̾ ���� ���, �÷��̾� �߰�
	if (me->DetectPlayer())
	{
		if (me->Trace()) return;
	}

	// ���� ���� �÷��̾ ���ų�, �÷��̾� �߰��� ���� ���
	// IDLE ���·� ��ȯ
	GetFsm().ChangeState(OBJECT_STATE::IDLE);
}

// ���� ����
void MonsterTraceState::Exit()
{
	exitTime = TimeManager::GetInstance().GetSecond();
}