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
	
	// ERROR
	// 활성상태인 오브젝트만 FinalTick이 돌아가서 플레이어가 현재 있는 맵의 보스몬스터만 상태를 빠져나가게 됨
	// 비활성상태인 보스몬스터는 여기 코드에 도달하지 못함

	// ERROR
	// 지웠더니 이상한값 가진객체가 FinalTick에서 돌아감
	//LevelManager::GetInstance().DeleteObject(*monster);
	//monster = nullptr;
	monster->SetActive(false);
}