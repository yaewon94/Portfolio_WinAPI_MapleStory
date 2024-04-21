#include "PCH.h"
#include "MonsterDeadState.h"
#include "LevelManager.h"
#include "FSM.h"

// 생성자
MonsterDeadState::MonsterDeadState(float Duration) : DeadState(Duration)
{
}

// 복사 생성자
MonsterDeadState::MonsterDeadState(const DeadState& origin) : DeadState(origin)
{
}

// 소멸자
MonsterDeadState::~MonsterDeadState()
{
}

// 상태 종료
void MonsterDeadState::Exit()
{
	//DeadState::Exit();
	
	// 몬스터 오브젝트 파괴
	GameObject* monster = GetFsm().GetOwner();
	LevelManager::GetInstance().DeleteObjectFromList(*monster);
	monster->Destroy();
	monster = nullptr;
}