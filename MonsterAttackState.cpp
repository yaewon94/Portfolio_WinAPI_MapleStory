#include "PCH.h"
#include "MonsterAttackState.h"
#include "FSM.h"
#include "Monster.h"
#include "TimeManager.h"

// ������
MonsterAttackState::MonsterAttackState(float coolDown) 
	: State(OBJECT_STATE::ATTACK, coolDown), me(nullptr)
{
}

// ���� ������
MonsterAttackState::MonsterAttackState(const MonsterAttackState& origin) : State(origin), me(nullptr)
{
}

// �Ҹ���
MonsterAttackState::~MonsterAttackState()
{
	me = nullptr;
}

// �ʱ�ȭ
void MonsterAttackState::Init()
{
	State::Init();
	me = (Monster*)GetFsm().GetOwner();
}

// ���� ����
void MonsterAttackState::Enter()
{
	me->Attack();
}

// ���� ����
void MonsterAttackState::Exit()
{
	exitTime = TimeManager::GetInstance().GetSecond();
}