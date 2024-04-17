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
#include "Texture.h"
#include "TimeManager.h"
#include "UI.h"
#include "Wall.h"

// 생성자
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"윌 1페이즈")
{
}

// 소멸자
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
	moonlight_gauge_skill = nullptr;
	moonlight_gauge_ratio_obj = nullptr;
}

// 레벨 진입시 호출
void Level_Boss_Will_Phase1::Enter()
{
	// [ERROR] 이렇게 해도 몇초있다가 이미지 사라짐 뭐지
	//textureBufferTest = AssetManager::GetInstance().LoadTexture(L"달빛게이지 배경_img", L"UI_MoonlightGauge_bgr.png");
	//gauge_bgr->SetTexture(textureBufferTest);
	

	// [임시 하드코딩]
	// [UI] 달빛 게이지
	GameObject* gauge_effect = AddObject(UI(L"달빛게이지 이펙트", Vec2(120.f, 200.f)));
	Animator* animator = gauge_effect->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::ANIM_DEFAULT, AssetManager::GetInstance().LoadTexture(L"달빛게이지 이펙트_anim", L"UI_MoonlightGauge_effect.png"), 8);
	animator->ChangeAnimation(OBJECT_STATE::ANIM_DEFAULT);

	GameObject* gauge_bgr = AddObject(UI(L"달빛게이지 배경", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE));
	gauge_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"달빛게이지 배경_img", L"UI_MoonlightGauge_bgr.png"));
	gauge_bgr->SetParent(*gauge_effect);

	moonlight_gauge_ratio_obj = AddObject(UI(L"달빛게이지 퍼센트", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE * 0.7f));
	moonlight_gauge_ratio_obj->SetTexture(AssetManager::GetInstance().LoadTexture(L"달빛게이지 게이지_img", L"UI_MoonlightGauge_fill.png"));
	moonlight_gauge_ratio_obj->SetParent(*gauge_bgr);

	moonlight_gauge_state_icon = AddObject(UI(L"달빛게이지 상태", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE));
	moonlight_gauge_state_icon->SetParent(*moonlight_gauge_ratio_obj);
	moonlight_gauge_state_icon->AddComponent<FSM>();
	animator = moonlight_gauge_state_icon->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED, AssetManager::GetInstance().LoadTexture(L"달빛게이지 사용 불가능", L"UI_MoonlightGauge_disabled.png"), 1);
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_ABLED, AssetManager::GetInstance().LoadTexture(L"달빛게이지 사용 가능", L"UI_MoonlightGauge_abled.png"), 1);

	// [UI] 보스몬스터 윌 체력바
	GameObject* will_hpbar_bgr = AddObject(UI(L"윌 HP바 배경", Vec2(960.f, 50.f), Vec2(1200, 60)));
	will_hpbar_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"윌 HP바 배경_img", L"UI_BossWill_HPbar_bgr.png"));
	GameObject* will_hpbar_fill_blue = AddObject(UI(L"윌 HP바 파란게이지", Vec2(27.f, 9.f), Vec2(1130, 7)));
	will_hpbar_fill_blue->SetTexture(AssetManager::GetInstance().LoadTexture(L"윌 HP바 파란게이지_img", L"UI_BossWill_HPbar_fill_blue.png"));
	will_hpbar_fill_blue->SetParent(*will_hpbar_bgr);

	// 배경
	GameObject& background = *AddObject(Background());

	// 지면
	GameObject* ground = AddObject(Ground());
	ground->SetParent(background);

	// 벽
	Wall* wall = (Wall*)AddObject(Wall());
	wall->SetParent(background);
	AddObject(Wall(*wall));

	// 몬스터
	// 몬스터는 객체마다 특성이 다르므로, 클래스 외부에서 특성에 맞게 컴포넌트 추가
	// 원래는 DB같은데서 받아와서 몬스터 클래스 내부에서 초기화 해야 함
	// 파란공간 윌
	Monster* boss_will = (Monster*)AddObject(Monster(L"Boss_Will", WILL_MAX_HP));
	boss_will->SetParent(background);
	boss_will->SetHPbar(*will_hpbar_fill_blue->GetTexture());
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
	SetPlayer((Player*)AddObject(Player(L"Player")));
	Player& player = GetPlayer();
	player.SetParent(background);
	// 달빛게이지 스킬 부여
	moonlight_gauge_skill = (ActiveSkill*)&player.AddSkill(SkillManager::GetInstance().GetSkill(1));
	player.AddSkillKeyMap(KEY_CODE::N, *moonlight_gauge_skill);
	OnChangeGaugePercent(player.GetCurrentSkillCost());	// 남은 스킬코스트에 맞는 달빛게이지 애니메이션 재생 용도

	// 맵 진입
	player.ChangeMap(MapManager::GetInstance().GetMap(0));
	//player.ChangeMap(MapManager::GetInstance().GetMap(1)); // 보라맵 테스트
}

// 레벨 종료시 호출
void Level_Boss_Will_Phase1::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}

// 매 프레임마다 호출
void Level_Boss_Will_Phase1::FinalTick()
{
	static float time = 0.f;

	// 최상위 FinalTick() 호출
	Level::FinalTick();

	// 일정 시간마다 달빛게이지 회복
	if (time > INTERVAL_OF_FILL_GAUGE)
	{
		if(GetPlayer().GetCurrentSkillCost() < MAX_GAUGE_MOONLIGHT) GetPlayer().FillSkillCost(RECOVERY_AMOUNT_OF_GAUGE);
		time = 0.f;
	}
	else
	{
		time += TimeManager::GetInstance().GetDeltaTime();
	}
}

// 달빛게이지 퍼센트 변화가 있을 때 호출
void Level_Boss_Will_Phase1::OnChangeGaugePercent(int currentSkillCost)
{
	// 달빛게이지
	OBJECT_STATE state;

	// TODO : 게이지 퍼센트별 이미지 변화
	moonlight_gauge_ratio_obj->GetTexture()->SetSliceRatio((float)currentSkillCost / MAX_GAUGE_MOONLIGHT, 1.f);

	// 상태 아이콘 변화
	if (currentSkillCost >= moonlight_gauge_skill->GetCost()) state = OBJECT_STATE::MOONLIGHT_GAUGE_ABLED;
	else state = OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED;
	moonlight_gauge_state_icon->GetComponent<FSM>()->ChangeState(state);
}