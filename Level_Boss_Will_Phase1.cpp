#include "PCH.h"
#include "Level_Boss_Will_Phase1.h"
#include "Animator.h"
#include "AssetManager.h"
#include "Background.h"
#include "Collider.h"
#include "FSM.h"
#include "GameObject.h"
#include "Ground.h"
#include "Map.h"
#include "Monster.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "Rigidbody.h"

// 생성자
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"윌 1페이즈")
{
}

// 소멸자
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
}

// 레벨 진입시 호출
void Level_Boss_Will_Phase1::Enter()
{
	// 플레이어 추가
	//GameObject* player = AddObject(Player(L"Player", Vec2(0.f, 900.f), Vec2(50, 70)));
	GameObject* player = AddObject(Player(L"Player", Vec2(0.f, -900.f), Vec2(50, 70)));


	// 맵 추가
	currentMap = &AddMap(*new Map(L"회절의 회랑", Vec2(0.f, 0.f), Vec2(1920, 2530), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_background", L"BossWill_Phase1_background.png")));

	// 그 외 오브젝트 추가
	GameObject* background = AddObject(Background());
	GameObject* ground = AddObject(Ground(Vec2(0.f, 1000.f), Vec2(1920, 20)));
	player->SetParent(*background);
	ground->SetParent(*background);
	// [임시]
	// 몬스터는 객체마다 특성이 다르므로, 클래스 외부에서 특성에 맞게 컴포넌트 추가
	// 원래는 DB같은데서 받아와서 몬스터 클래스 내부에서 초기화 해야 함
	GameObject* boss_will = AddObject(Monster(L"Boss_Will", Vec2(500.f, 950.f)));
	boss_will->SetParent(*background);
	FSM* fsm = boss_will->AddComponent<FSM>();
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	Animator* animator = boss_will->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);

	// 맵 진입
	currentMap->Enter();
}

// 레벨 종료시 호출
void Level_Boss_Will_Phase1::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}