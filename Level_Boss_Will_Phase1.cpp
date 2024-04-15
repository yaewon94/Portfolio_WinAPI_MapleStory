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
	// �÷��̾� �߰�
	//GameObject* player = AddObject(Player(L"Player", Vec2(0.f, 900.f), Vec2(50, 70)));
	GameObject* player = AddObject(Player(L"Player", Vec2(0.f, -900.f), Vec2(50, 70)));


	// �� �߰�
	currentMap = &AddMap(*new Map(L"ȸ���� ȸ��", Vec2(0.f, 0.f), Vec2(1920, 2530), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_background", L"BossWill_Phase1_background.png")));

	// �� �� ������Ʈ �߰�
	GameObject* background = AddObject(Background());
	GameObject* ground = AddObject(Ground(Vec2(0.f, 1000.f), Vec2(1920, 20)));
	player->SetParent(*background);
	ground->SetParent(*background);
	// [�ӽ�]
	// ���ʹ� ��ü���� Ư���� �ٸ��Ƿ�, Ŭ���� �ܺο��� Ư���� �°� ������Ʈ �߰�
	// ������ DB�������� �޾ƿͼ� ���� Ŭ���� ���ο��� �ʱ�ȭ �ؾ� ��
	GameObject* boss_will = AddObject(Monster(L"Boss_Will", Vec2(500.f, 950.f)));
	boss_will->SetParent(*background);
	FSM* fsm = boss_will->AddComponent<FSM>();
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	Animator* animator = boss_will->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);

	// �� ����
	currentMap->Enter();
}

// ���� ����� ȣ��
void Level_Boss_Will_Phase1::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}