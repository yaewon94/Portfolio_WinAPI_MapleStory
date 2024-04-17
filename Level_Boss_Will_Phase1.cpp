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

// ������
Level_Boss_Will_Phase1::Level_Boss_Will_Phase1() : Level(L"�� 1������")
{
}

// �Ҹ���
Level_Boss_Will_Phase1::~Level_Boss_Will_Phase1()
{
	gauge_skill = nullptr;
	gauge_percent = nullptr;
}

// ���� ���Խ� ȣ��
void Level_Boss_Will_Phase1::Enter()
{
	// [ERROR] �̷��� �ص� �����ִٰ� �̹��� ����� ����
	//textureBufferTest = AssetManager::GetInstance().LoadTexture(L"�޺������� ���_img", L"UI_MoonlightGauge_bgr.png");
	//gauge_bgr->SetTexture(textureBufferTest);
	

	// [�ӽ� �ϵ��ڵ�]
	// UI
	// �޺� ������
	GameObject* gauge_effect = AddObject(UI(L"�޺������� ����Ʈ", GAUGE_POS, GAUGE_SCALE));
	Animator* animator = gauge_effect->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::ANIM_DEFAULT, AssetManager::GetInstance().LoadTexture(L"�޺������� ����Ʈ_anim", L"UI_MoonlightGauge_effect.png"), 8);
	animator->ChangeAnimation(OBJECT_STATE::ANIM_DEFAULT);

	GameObject* gauge_bgr = AddObject(UI(L"�޺������� ���", DEFAULT_OBJECT_POS, GAUGE_SCALE));
	gauge_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"�޺������� ���_img", L"UI_MoonlightGauge_bgr.png"));
	gauge_bgr->SetParent(*gauge_effect);

	gauge_percent = AddObject(UI(L"�޺������� �ۼ�Ʈ", DEFAULT_OBJECT_POS, GAUGE_SCALE * 0.7f));
	gauge_percent->SetTexture(AssetManager::GetInstance().LoadTexture(L"�޺������� ������_img", L"UI_MoonlightGauge_fill.png"));
	gauge_percent->SetParent(*gauge_bgr);

	gauge_state = AddObject(UI(L"�޺������� ����", DEFAULT_OBJECT_POS, GAUGE_SCALE));
	gauge_state->SetParent(*gauge_percent);
	gauge_state->AddComponent<FSM>();
	animator = gauge_state->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED, AssetManager::GetInstance().LoadTexture(L"�޺������� ��� �Ұ���", L"UI_MoonlightGauge_disabled.png"), 1);
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_ABLED, AssetManager::GetInstance().LoadTexture(L"�޺������� ��� ����", L"UI_MoonlightGauge_abled.png"), 1);

	// ���
	GameObject& background = *AddObject(Background());

	// ����
	GameObject* ground = AddObject(Ground());
	ground->SetParent(background);

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
	SetPlayer((Player*)AddObject(Player(L"Player", Vec2(0.f, 0.f), Vec2(50, 70))));
	Player& player = GetPlayer();
	player.SetParent(background);
	// �޺������� ��ų �ο�
	gauge_skill = (ActiveSkill*)&player.AddSkill(SkillManager::GetInstance().GetSkill(1));
	player.AddSkillKeyMap(KEY_CODE::N, *gauge_skill);
	OnChangeGaugePercent(player.GetCurrentSkillCost());	// ���� ��ų�ڽ�Ʈ�� �´� �޺������� �ִϸ��̼� ��� �뵵

	// �� ����
	player.ChangeMap(MapManager::GetInstance().GetMap(0));
	//player.ChangeMap(MapManager::GetInstance().GetMap(1)); // ����� �׽�Ʈ
}

// ���� ����� ȣ��
void Level_Boss_Will_Phase1::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}

// �� �����Ӹ��� ȣ��
void Level_Boss_Will_Phase1::FinalTick()
{
	static float time = 0.f;

	// �ֻ��� FinalTick() ȣ��
	Level::FinalTick();

	// ���� �ð����� �޺������� ȸ��
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

// �޺������� �ۼ�Ʈ ��ȭ�� ���� �� ȣ��
void Level_Boss_Will_Phase1::OnChangeGaugePercent(int currentSkillCost)
{
	// �޺�������
	OBJECT_STATE state;

	// TODO : ������ �ۼ�Ʈ�� �̹��� ��ȭ
	gauge_percent->GetTexture()->SetSliceRatio((float)currentSkillCost / MAX_GAUGE_MOONLIGHT, 1.f);

	// ���� ������ ��ȭ
	if (currentSkillCost >= gauge_skill->GetCost()) state = OBJECT_STATE::MOONLIGHT_GAUGE_ABLED;
	else state = OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED;
	gauge_state->GetComponent<FSM>()->ChangeState(state);
}