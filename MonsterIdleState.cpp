#include "PCH.h"
#include "MonsterIdleState.h"
#include "FSM.h"
#include "Monster.h"

// ������
MonsterIdleState::MonsterIdleState() : me(nullptr)
{
}

// �Ҹ���
MonsterIdleState::~MonsterIdleState()
{
	me = nullptr;
}

// �ʱ�ȭ
void MonsterIdleState::Init()
{
	me = (Monster*)GetFsm().GetOwner();
}

// ���� ����
void MonsterIdleState::Enter()
{
	IdleState::Enter();
}

// �� �����Ӹ��� ȣ��
void MonsterIdleState::Stay()
{
	// ���� ���� �÷��̾ �����Ǹ�, ���� ���·� ��ȯ
	if (me->DetectPlayer()) GetFsm().ChangeState(OBJECT_STATE::TRACE);
}