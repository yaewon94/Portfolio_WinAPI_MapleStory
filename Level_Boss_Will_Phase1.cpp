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

// ������
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"�� 1������"), gauge_moonlight(nullptr)
{
}

// �Ҹ���
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
	// ������Ʈ ��ü ���Ŵ� Level ���
	gauge_moonlight = nullptr;
}

// ���� ���Խ� ȣ��
void Level_Boss_Will_Phase1::Enter()
{
	// [�ӽ� �ϵ��ڵ�]
	// UI
	gauge_moonlight = AddObject(UI(L"�޺�������", Vec2(120.f, 200.f)));
	Animator* animator = gauge_moonlight->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_0, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_0", L"UI_MoonlightGauge_0.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_20, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_20", L"UI_MoonlightGauge_20.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_40, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_40", L"UI_MoonlightGauge_40.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_60, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_60", L"UI_MoonlightGauge_60.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_80, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_80", L"UI_MoonlightGauge_80.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_100, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_100", L"UI_MoonlightGauge_100.png"), 6);

	// ���
	GameObject& background = *AddObject(Background());

	// ����
	GameObject* obj = AddObject(Ground());
	obj->SetParent(background);

	// ��
	Wall* wall = (Wall*)AddObject(Wall());
	wall->SetParent(background);
	AddObject(Wall(*wall));

	// ����
	// ���ʹ� ��ü���� Ư���� �ٸ��Ƿ�, Ŭ���� �ܺο��� Ư���� �°� ������Ʈ �߰�
	// ������ DB�������� �޾ƿͼ� ���� Ŭ���� ���ο��� �ʱ�ȭ �ؾ� ��
	// �Ķ����� ��
	Monster* boss_will = (Monster*)AddObject(Monster(L"Boss_Will"));
	boss_will->SetParent(background);
	FSM* fsm = boss_will->AddComponent<FSM>();
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	animator = boss_will->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);
	boss_will->SetActive(false);
	// ������� ��
	AddObject(Monster(*boss_will));	// Clone()�ϸ� �ȉ�. AddObject() ���ο��� new �̿��ؼ� �����ϱ� ����

	// �÷��̾�
	obj = AddObject(Player(L"Player", Vec2(0.f, 0.f), Vec2(50, 70)));
	obj->SetParent(background);
	Player* player = (Player*)obj;
	// �޺������� ��ų �ο�
	ActiveSkill* activeSkill = (ActiveSkill*)&player->AddSkill(SkillManager::GetInstance().GetSkill(1));
	player->AddSkillKeyMap(KEY_CODE::N, *activeSkill);
	OnUseLevelSkill(player->GetCurrentSkillCost());	// ���� ��ų�ڽ�Ʈ�� �´� �޺������� �ִϸ��̼� ��� �뵵
	
	// �� ����
	player->ChangeMap(MapManager::GetInstance().GetMap(0));
	//player->ChangeMap(MapManager::GetInstance().GetMap(1)); // ����� �׽�Ʈ
}

// ���� ����� ȣ��
void Level_Boss_Will_Phase1::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}

// ���� ���������� �� �� �ִ� Ư���� ��ų�� ������� �� ȣ���
void Level_Boss_Will_Phase1::OnUseLevelSkill(int currentSkillCost)
{
	// �޺�������
	OBJECT_STATE gaugePercent;

	if (currentSkillCost == 100) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_100;
	else if (currentSkillCost >= 80) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_80;
	else if (currentSkillCost >= 60) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_60;
	else if (currentSkillCost >= 40) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_40;
	else if (currentSkillCost >= 20) gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_20;
	else gaugePercent = OBJECT_STATE::UI_MOONLIGHT_GAUGE_0;

	gauge_moonlight->GetComponent<Animator>()->ChangeAnimation(gaugePercent);
}