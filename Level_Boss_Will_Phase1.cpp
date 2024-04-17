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
	moonlight_gauge_skill = nullptr;
	moonlight_gauge_ratio_obj = nullptr;
}

// ���� ���Խ� ȣ��
void Level_Boss_Will_Phase1::Enter()
{
	// [ERROR] �̷��� �ص� �����ִٰ� �̹��� ����� ����
	//textureBufferTest = AssetManager::GetInstance().LoadTexture(L"�޺������� ���_img", L"UI_MoonlightGauge_bgr.png");
	//gauge_bgr->SetTexture(textureBufferTest);
	

	// [�ӽ� �ϵ��ڵ�]
	// [UI] �޺� ������
	GameObject* gauge_effect = AddObject(UI(L"�޺������� ����Ʈ", Vec2(120.f, 200.f)));
	Animator* animator = gauge_effect->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::ANIM_DEFAULT, AssetManager::GetInstance().LoadTexture(L"�޺������� ����Ʈ_anim", L"UI_MoonlightGauge_effect.png"), 8);
	animator->ChangeAnimation(OBJECT_STATE::ANIM_DEFAULT);

	GameObject* gauge_bgr = AddObject(UI(L"�޺������� ���", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE));
	gauge_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"�޺������� ���_img", L"UI_MoonlightGauge_bgr.png"));
	gauge_bgr->SetParent(*gauge_effect);

	moonlight_gauge_ratio_obj = AddObject(UI(L"�޺������� �ۼ�Ʈ", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE * 0.7f));
	moonlight_gauge_ratio_obj->SetTexture(AssetManager::GetInstance().LoadTexture(L"�޺������� ������_img", L"UI_MoonlightGauge_fill.png"));
	moonlight_gauge_ratio_obj->SetParent(*gauge_bgr);

	moonlight_gauge_state_icon = AddObject(UI(L"�޺������� ����", DEFAULT_OBJECT_POS, MOONLIGHT_GAUGE_SCALE));
	moonlight_gauge_state_icon->SetParent(*moonlight_gauge_ratio_obj);
	moonlight_gauge_state_icon->AddComponent<FSM>();
	animator = moonlight_gauge_state_icon->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED, AssetManager::GetInstance().LoadTexture(L"�޺������� ��� �Ұ���", L"UI_MoonlightGauge_disabled.png"), 1);
	animator->AddAnimation(OBJECT_STATE::MOONLIGHT_GAUGE_ABLED, AssetManager::GetInstance().LoadTexture(L"�޺������� ��� ����", L"UI_MoonlightGauge_abled.png"), 1);

	// [UI] �������� �� ü�¹�
	GameObject* will_hpbar_bgr = AddObject(UI(L"�� HP�� ���", Vec2(960.f, 50.f), Vec2(1200, 60)));
	will_hpbar_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"�� HP�� ���_img", L"UI_BossWill_HPbar_bgr.png"));
	GameObject* will_hpbar_fill_blue = AddObject(UI(L"�� HP�� �Ķ�������", Vec2(27.f, 9.f), Vec2(1130, 7)));
	will_hpbar_fill_blue->SetTexture(AssetManager::GetInstance().LoadTexture(L"�� HP�� �Ķ�������_img", L"UI_BossWill_HPbar_fill_blue.png"));
	will_hpbar_fill_blue->SetParent(*will_hpbar_bgr);

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
	// ������� ��
	AddObject(Monster(*boss_will));	// Clone()�ϸ� �ȉ�. AddObject() ���ο��� new �̿��ؼ� �����ϱ� ����


	// �÷��̾�
	SetPlayer((Player*)AddObject(Player(L"Player")));
	Player& player = GetPlayer();
	player.SetParent(background);
	// �޺������� ��ų �ο�
	moonlight_gauge_skill = (ActiveSkill*)&player.AddSkill(SkillManager::GetInstance().GetSkill(1));
	player.AddSkillKeyMap(KEY_CODE::N, *moonlight_gauge_skill);
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
	moonlight_gauge_ratio_obj->GetTexture()->SetSliceRatio((float)currentSkillCost / MAX_GAUGE_MOONLIGHT, 1.f);

	// ���� ������ ��ȭ
	if (currentSkillCost >= moonlight_gauge_skill->GetCost()) state = OBJECT_STATE::MOONLIGHT_GAUGE_ABLED;
	else state = OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED;
	moonlight_gauge_state_icon->GetComponent<FSM>()->ChangeState(state);
}