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
#include "MapManager.h"
#include "Monster.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "UI.h"
#include "Wall.h"

// ������
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"�� 1������")
{
}

// �Ҹ���
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
}

// ���� ���Խ� ȣ��
void Level_Boss_Will_Phase1::Enter()
{
	// UI
	GameObject* obj = AddObject(UI(L"�޺�������", Vec2(120.f, 200.f)));
	Animator* animator = obj->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_0, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_0", L"UI_MoonlightGauge_0.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_20, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_20", L"UI_MoonlightGauge_20.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_40, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_40", L"UI_MoonlightGauge_40.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_60, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_60", L"UI_MoonlightGauge_60.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_80, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_80", L"UI_MoonlightGauge_80.png"), 1);
	animator->AddAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_100, AssetManager::GetInstance().LoadTexture(L"UI_MoonlightGauge_100", L"UI_MoonlightGauge_100.png"), 6);
	animator->ChangeAnimation(OBJECT_STATE::UI_MOONLIGHT_GAUGE_0);

	// ���
	GameObject& background = *AddObject(Background());

	// ����
	obj = AddObject(Ground());
	obj->SetParent(background);

	// ��
	obj = AddObject(Wall());
	obj->SetParent(background);
	obj = AddObject(Wall());
	obj->SetParent(background);

	// [�ӽ� �ϵ��ڵ�] ����
	// ���ʹ� ��ü���� Ư���� �ٸ��Ƿ�, Ŭ���� �ܺο��� Ư���� �°� ������Ʈ �߰�
	// ������ DB�������� �޾ƿͼ� ���� Ŭ���� ���ο��� �ʱ�ȭ �ؾ� ��
	// �Ķ����� ��
	GameObject* boss_will = AddObject(Monster(L"Boss_Will", Vec2(500.f, 300.f)));
	boss_will->SetParent(background);
	FSM* fsm = boss_will->AddComponent<FSM>();
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	animator = boss_will->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);

	// �÷��̾�
	obj = AddObject(Player(L"Player", Vec2(0.f, 300.f), Vec2(50, 70)));
	obj->SetParent(background);
	Player* player = (Player*)obj;
	// TODO : �޺������� ��ų �߰�
	
	// �� ����
	player->ChangeMap(MapManager::GetInstance().GetMap(0));
}

// ���� ����� ȣ��
void Level_Boss_Will_Phase1::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}