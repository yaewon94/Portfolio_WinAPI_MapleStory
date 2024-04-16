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

// ���� ������
MonsterTraceState::MonsterTraceState(const MonsterTraceState& origin) : State(origin), me(nullptr)
{
	// ��������� ȣ������� owner�� nullptr�� me�� ���߿� �ʱ�ȭ ����� ��
	// TODO : Init() ȣ�� ���ϴ� ��ü �ִ��� üũ
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