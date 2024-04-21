#include "PCH.h"
#include "MonsterDeadState.h"
#include "LevelManager.h"
#include "FSM.h"

// ������
MonsterDeadState::MonsterDeadState(float Duration) : DeadState(Duration)
{
}

// ���� ������
MonsterDeadState::MonsterDeadState(const DeadState& origin) : DeadState(origin)
{
}

// �Ҹ���
MonsterDeadState::~MonsterDeadState()
{
}

// ���� ����
void MonsterDeadState::Exit()
{
	//DeadState::Exit();
	
	// ���� ������Ʈ �ı�
	GameObject* monster = GetFsm().GetOwner();
	LevelManager::GetInstance().DeleteObjectFromList(*monster);
	monster->Destroy();
	monster = nullptr;
}