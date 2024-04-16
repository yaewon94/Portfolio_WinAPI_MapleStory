#include "PCH.h"
#include "Level_Boss_Will_Phase1.h"
#include "ActiveSkill.h"
#include "Animator.h"
#include "AssetManager.h"
#include "Background.h"
#include "Collider.h"
#include "FSM.h"
#include "GameObject.h"
#include "Ground.h"
#include "Map.h"
#include "MapManager.h"
#include "Monster.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "UI.h"
#include "Wall.h"

// 생성자
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"윌 1페이즈"), gauge_moonlight(nullptr)
{
}

// 소멸자
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
	// 오브젝트 객체 제거는 Level 담당
	gauge_moonlight = nullptr;
}

// 레벨 진입시 호출
void Level_Boss_Will_Phase1::Enter()
{
	// [임시 하드코딩]
	// UI
	gauge_moonlight = AddObject(UI(L"달빛게이지", Vec2(120.f, 200.f)));
	Animator* animator = gauge_moonlight->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_0, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_0", L"UI_MoonlightGauge_0.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_20, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_20", L"UI_MoonlightGauge_20.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_40, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_40", L"UI_MoonlightGauge_40.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_60, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_60", L"UI_MoonlightGauge_60.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_80, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_80", L"UI_MoonlightGauge_80.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_100, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_100", L"UI_MoonlightGauge_100.png"), 6);

	// 배경
	GameObject& background = *AddObject(Background());

	// 지면
	GameObject* obj = AddObject(Ground());
	obj->SetParent(background);

	// 벽
	Wall* wall = (Wall*)AddObject(Wall());
	wall->SetParent(background);
	AddObject(Wall(*wall));

	// 몬스터
	// 몬스터는 객체마다 특성이 다르므로, 클래스 외부에서 특성에 맞게 컴포넌트 추가
	// 원래는 DB같은데서 받아와서 몬스터 클래스 내부에서 초기화 해야 함
	// 파란공간 윌
	Monster* boss_will = (Monster*)AddObject(Monster(L"Boss_Will"));
	boss_will->SetParent(background);
	FSM* fsm = boss_will->AddComponent<FSM>();
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	animator = boss_will->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);
	boss_will->SetActive(false);
	// 보라공간 윌
	AddObject(Monster(*boss_will));	// Clone()하면 안됌. AddObject() 내부에서 new 이용해서 생성하기 때문

	// 플레이어
	obj = AddObject(Player(L"Player", Vec2(0.f, 0.f), Vec2(50, 70)));
	obj->SetParent(background);
	Player* player = (Player*)obj;
	// 달빛게이지 스킬 부여
	ActiveSkill* activeSkill = (ActiveSkill*)&player->AddSkill(SkillManager::GetInstance().GetSkill(1));
	player->AddSkillKeyMap(KEY_CODE::N, *activeSkill);
	OnUseLevelSkill(player->GetCurrentSkillCost());	// 남은 스킬코스트에 맞는 달빛게이지 애니메이션 재생 용도
	
	// 맵 진입
	player->ChangeMap(MapManager::GetInstance().GetMap(0));
	//player->ChangeMap(MapManager::GetInstance().GetMap(1)); // 보라맵 테스트
}

// 레벨 종료시 호출
void Level_Boss_Will_Phase1::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}

// 현재 레벨에서만 쓸 수 있는 특수한 스킬을 사용했을 때 호출됨
void Level_Boss_Will_Phase1::OnUseLevelSkill(int currentSkillCost)
{
	// 달빛게이지
	OBJECT_STATE gaugePercent;

	if (currentSkillCost == 100) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_100;
	else if (currentSkillCost >= 80) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_80;
	else if (currentSkillCost >= 60) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_60;
	else if (currentSkillCost >= 40) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_40;
	else if (currentSkillCost >= 20) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_20;
	else gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_0;

	gauge_moonlight->GetComponent<Animator>()->ChangeAnimation(gaugePercent);
}