#include "PCH.h"
#include "MonsterIdleState.h"
#include "FSM.h"
#include "Monster.h"

// ������
MonsterIdleState::MonsterIdleState() : State(OBJECT_STATE::IDLE), me(nullptr)
{
}

// ���� ������
MonsterIdleState::MonsterIdleState(const MonsterIdleState& origin) : State(origin), me(nullptr)
{
	// ��������� ȣ������� owner�� nullptr�� me�� ���߿� �ʱ�ȭ ����� ��
	// TODO : Init() ȣ�� ���ϴ� ��ü �ִ��� üũ
}

// �Ҹ���
MonsterIdleState::~MonsterIdleState()
{
	me = nullptr;
}

// �ʱ�ȭ
void MonsterIdleState::Init()
{
	State::Init();
	me = (Monster*)GetFsm().GetOwner();
}

// �� �����Ӹ��� ȣ��
void MonsterIdleState::Stay()
{
	// ���� ���� �÷��̾ �����Ǹ�, ���� ���·� ��ȯ
	if (me->DetectPlayer()) GetFsm().ChangeState(OBJECT_STATE::TRACE);
	// �������� ������ ���ݻ��� ��ȯ
	else GetFsm().ChangeState(OBJECT_STATE::ATTACK);
}