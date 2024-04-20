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
	State::Init();
	me = (Monster*)GetFsm().GetOwner();
}

// �� �����Ӹ��� ȣ��
void MonsterTraceState::Stay()
{
	// ���� ���� �÷��̾ �ִ��� ��� ����
	if (me->DetectPlayer())
	{
		// �÷��̾� ��ó�� ������ ��� ���ݻ��·� ��ȯ
		if (me->Trace()) GetFsm().ChangeState(OBJECT_STATE::ATTACK);
	}
	else
	{
		// ���� ���� �÷��̾ ������� ����Ʈ���·� ��ȯ
		GetFsm().ChangeState(GetFsm().GetDefaultState());
	}
}

// ���� ����
void MonsterTraceState::Exit()
{
	exitTime = TimeManager::GetInstance().GetSecond();
}