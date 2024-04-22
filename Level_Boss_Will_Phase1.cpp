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
#include "Player.h"
#include "RandomManager.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillSummonerObject.h"
#include "Sound.h"
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
	// [�ӽ� �ϵ��ڵ�]
	// [UI] �޺� ������
	GameObject* gauge_effect = AddObject(UI(L"�޺������� ����Ʈ", Vec2(120.f, 200.f)));
	Animator* animator = gauge_effect->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::DEFAULT, AssetManager::GetInstance().LoadTexture(L"�޺������� ����Ʈ_anim", L"UI_MoonlightGauge_effect.png"), 8);
	animator->ChangeAnimation(OBJECT_STATE::DEFAULT);

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
	// �Ķ����� �� + ������� �� ü�¹� ��ü
	willHP_gauge_total = AddObject(UI(L"�� HP�� ��ü", Vec2(27.f, -15.f), Vec2(1134, 15)));
	willHP_gauge_total->SetTexture(AssetManager::GetInstance().LoadTexture(L"���� HP�� ������_img", L"UI_Monster_HPbar_gauge.png"));
	willHP_gauge_total->SetParent(*will_hpbar_bgr);
	// �Ķ����� �� ü�¹�
	GameObject* will_hpbar_fill_blue = AddObject(UI(L"�� HP�� �Ķ�������", Vec2(27.f, 9.f), Vec2(1130, 7)));
	will_hpbar_fill_blue->SetTexture(AssetManager::GetInstance().LoadTexture(L"�� HP�� �Ķ�������_img", L"UI_BossWill_HPbar_fill_blue.png"));
	will_hpbar_fill_blue->SetParent(*will_hpbar_bgr);
	// ������� �� ü�¹�
	GameObject* will_hpbar_fill_pupple = AddObject(UI(L"�� HP�� ���������", Vec2(27.f, 20.f), Vec2(1130, 7)));
	will_hpbar_fill_pupple->SetTexture(AssetManager::GetInstance().LoadTexture(L"�� HP�� ���������_img", L"UI_BossWill_HPbar_fill_pupple.png"));
	will_hpbar_fill_pupple->SetParent(*will_hpbar_bgr);

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
	// TODO : DB ���� �޾ƿͼ� �����͸Ŵ��� ���� �ʱ�ȭ
	// �Ķ����� ��
	bossWill_blue = (Monster*)AddObject(Monster(L"Boss_Will", WILL_MAX_HP));
	bossWill_blue->SetParent(background);
	bossWill_blue->SetHPbar(*will_hpbar_fill_blue->GetTexture());
	animator = bossWill_blue->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Idle", L"BossWill_Phase1_Idle.png"), 8);
	animator->AddAnimation(OBJECT_STATE::TRACE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Move", L"BossWill_Phase1_Move.png"), 8);
	animator->AddAnimation(OBJECT_STATE::DEAD, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_Dead", L"BossWill_Phase1_Dead.png"), 8);
	animator->AddAnimation(OBJECT_STATE::BOSSWILL_ATTACK_MELEE, AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_MeleeAttack", L"BossWill_Phase1_MeleeAttack.png"), 20, false);
	bossWill_blue->SetActive(false);
	// ��ų�߰�
	bossWill_blue->AddSkill(SkillManager::GetInstance().GetSkill(2));
	// ������� �� (�Ķ����� �� Ŭ��)
	bossWill_pupple = (Monster*)AddObject(Monster(*bossWill_blue));	// Clone()�ϸ� �ȉ�. AddObject() ���ο��� new �̿��ؼ� �����ϱ� ����
	bossWill_pupple->SetHPbar(*will_hpbar_fill_pupple->GetTexture());
	// �ֽ��ϴ� ������
	watchingEyes[0] = (SkillSummonerObject*)AddObject(SkillSummonerObject(L"�ֽ��ϴ� ������", LAYER_TYPE::ENEMY, 3, (EnemyAttackSkill&)SkillManager::GetInstance().GetSkill(3)));
	watchingEyes[0]->SetOffset(Vec2(0.f, -100.f));
	watchingEyes[0]->SetParent(background);
	watchingEyes[0]->AddSkillVelocity(Vec2(0.f, 800.f), 0);
	watchingEyes[0]->AddSkillVelocity(Vec2(-300.f, 800.f), 1);
	watchingEyes[0]->AddSkillVelocity(Vec2(300.f, 800.f), 2);
	animator = watchingEyes[0]->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::DEFAULT, AssetManager::GetInstance().LoadTexture(L"�ֽ��ϴ� ������", L"Skill_WatchingEye.png"), 16);
	animator->ChangeAnimation(OBJECT_STATE::DEFAULT);
	watchingEyes[0]->SetActive(false);
	watchingEyes[1] = (SkillSummonerObject*)AddObject(*watchingEyes[0]->Clone());
	watchingEyes[1]->SetOffset(Vec2(-600.f, -100.f));
	watchingEyes[1]->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::DEFAULT);
	watchingEyes[2] = (SkillSummonerObject*)AddObject(*watchingEyes[0]->Clone());
	watchingEyes[2]->SetOffset(Vec2(600.f, -100.f));
	watchingEyes[2]->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::DEFAULT);
	// �Ź̴ٸ� �������
	spiderLegs[0] = (SkillSummonerObject*)AddObject(SkillSummonerObject(L"�Ź̴ٸ� �������", LAYER_TYPE::ENEMY, 1, (EnemyAttackSkill&)SkillManager::GetInstance().GetSkill(4)));
	spiderLegs[0]->SetOffset(Vec2(-750.f, 0.f));
	spiderLegs[0]->SetSkillObjectOffset(-50.f, 0.f);
	spiderLegs[0]->SetParent(background);
	animator = spiderLegs[0]->AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::DEFAULT, AssetManager::GetInstance().LoadTexture(L"�Ź̴ٸ� �������", L"Skill_SpiderLeg.png"), 12, false);
	animator->ChangeAnimation(OBJECT_STATE::DEFAULT);
	spiderLegs[0]->SetActive(false);
	spiderLegs[1] = (SkillSummonerObject*)AddObject(*spiderLegs[0]->Clone());
	spiderLegs[1]->SetOffset(Vec2(-250.f, 0.f));
	spiderLegs[1]->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::DEFAULT);
	spiderLegs[2] = (SkillSummonerObject*)AddObject(*spiderLegs[0]->Clone());
	spiderLegs[2]->SetOffset(Vec2(250.f, 0.f));
	spiderLegs[2]->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::DEFAULT);
	spiderLegs[3] = (SkillSummonerObject*)AddObject(*spiderLegs[0]->Clone());
	spiderLegs[3]->SetOffset(Vec2(750.f, 0.f));
	spiderLegs[3]->GetComponent<Animator>()->ChangeAnimation(OBJECT_STATE::DEFAULT);

	// �÷��̾�
	SetPlayer((Player*)AddObject(Player(L"Player")));
	Player& player = GetPlayer();
	player.SetParent(background);
	// �޺������� ��ų �ο�
	moonlight_gauge_skill = (ActiveSkill*)&player.AddSkill(SkillManager::GetInstance().GetSkill(1));
	player.AddSkillKeyMap(KEY_CODE::N, *moonlight_gauge_skill);
	player.FillSkillCost(MAX_GAUGE_MOONLIGHT);	// TEST : �޺������� �ִ�� �ο�
	OnChangeGaugePercent(player.GetCurrentSkillCost());	// ���� ��ų�ڽ�Ʈ�� �´� �޺������� �ִϸ��̼� ��� �뵵

	// [UI] �÷��̾� ü�¹�
	GameObject* player_hpbar_bgr = AddObject(UI(L"�÷��̾� ���¹� ���", Vec2(960.f, 980.f), Vec2(306, 81)));
	player_hpbar_bgr->SetTexture(AssetManager::GetInstance().LoadTexture(L"�÷��̾� ���¹� ���", L"UI_Player_StatusBar_bgr.png"));
	// �÷��̾� ü�¹� ������
	GameObject* player_hpbar_fill = AddObject(UI(L"�÷��̾� HP�� ������", Vec2(13.f, 11.f), Vec2(256, 17)));
	player_hpbar_fill->SetTexture(AssetManager::GetInstance().LoadTexture(L"�÷��̾� HP�� ������", L"UI_Player_HPbar_fill.png"));
	player_hpbar_fill->SetParent(*player_hpbar_bgr);
	player.SetHPbar(*player_hpbar_fill->GetTexture());

	// �� ����
	player.ChangeMap(MapManager::GetInstance().GetMap(0));
	//player.ChangeMap(MapManager::GetInstance().GetMap(1)); // ����� �׽�Ʈ

	//// ���� �ε�
	Sound* sound = AssetManager::GetInstance().LoadSound(L"�� 1�� ���", L"Sound_Boss_Will.wav");
	sound->SetVolume(100.f);
	sound->Play(true);
}

// ���� ����� ȣ��
void Level_Boss_Will_Phase1::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}

// �� �����Ӹ��� ȣ��
void Level_Boss_Will_Phase1::Tick()
{
	// �ֻ��� Tick() ȣ��
	Level::Tick();

	if (isSucceed) return;

	// ���� �ֱ⸶�� �� ��ü��ų ����
	static float time = 0.f;
	time += TimeManager::GetInstance().GetDeltaTime();
	if (time > INTERVAL_SUMMON_MONSTER)
	{
		time = 0.f;

		int param = RandomManager::Create(12);
		SummonSpiderLegs(param);
		SummonWatchingEyes(param);
	}
}

// �� �����Ӹ��� ȣ��
void Level_Boss_Will_Phase1::FinalTick()
{
	// �ֻ��� FinalTick() ȣ��
	Level::FinalTick();

	// ���� ���̵� ���� ȣ��
	if (isSucceed) return;

	// ���� �ð����� �޺������� ȸ��
	static float time = 0.f;
	time += TimeManager::GetInstance().GetDeltaTime();
	if (time > INTERVAL_OF_FILL_GAUGE)
	{
		if (GetPlayer().GetCurrentSkillCost() < MAX_GAUGE_MOONLIGHT) GetPlayer().FillSkillCost(RECOVERY_AMOUNT_OF_GAUGE);
		time = 0.f;
	}
	
	// �÷��̾ ������ ü���� �� ���� ���� ���� �������� ������ ü���� ȸ����Ŵ
	static bool isFilledHP = false;
	auto playerState = GetPlayer().GetComponent<FSM>()->GetCurrentState();
	if (playerState == OBJECT_STATE::DEAD_BEFORE || playerState == OBJECT_STATE::DEAD)
	{
		if (!isFilledHP)
		{
			isFilledHP = true;

			int blueHP = bossWill_blue->GetCurrentHP();
			int puppleHP = bossWill_pupple->GetCurrentHP();

			if (blueHP > puppleHP) bossWill_pupple->FillHP(blueHP - puppleHP);
			else bossWill_blue->FillHP(puppleHP - blueHP);
		}
	}
	else
	{
		isFilledHP = false;
	}
}

// TODO : ü�°����� �������� Ŭ������ ����, �ű⼭ ü�� ����
// ���������� ü���� 0�� �Ǿ��� �� ȣ��
void Level_Boss_Will_Phase1::OnAlertBossHpZero()
{
	static int count = 0;
	++count;

	if (count == COUNT_PER_SUMMON)
	{
		count = 0;

		// �� ��üü�� ���簪 ����
		willHP_cur_total -= WILL_MAX_HP * COUNT_PER_SUMMON;

		// ü�¹� UI�� �ݿ�
		willHP_gauge_total->GetTexture()->SetSliceRatio((float)willHP_cur_total / WillHP_max_total, 1.f);

		// �������� ���� ��ȯ, óġ���� �÷��� ����
		isSucceed = true;
		bossWill_blue->GetComponent<FSM>()->ChangeState(OBJECT_STATE::DEAD_BEFORE);
		bossWill_pupple->GetComponent<FSM>()->ChangeState(OBJECT_STATE::DEAD_BEFORE);

		// �÷��̾ �޺������� ��ų ��� ���ϰ� ����
		SkillManager::GetInstance().SetValid(&GetPlayer().GetSkill(KEY_CODE::N), false);

		// TODO : �ð��Ǹ� óġ���� UI ���
	}
}

// �޺������� �ۼ�Ʈ ��ȭ�� ���� �� ȣ��
void Level_Boss_Will_Phase1::OnChangeGaugePercent(int currentSkillCost)
{
	// �޺�������
	OBJECT_STATE state;

	// ������ �ۼ�Ʈ�� �̹��� ��ȭ
	moonlight_gauge_ratio_obj->GetTexture()->SetSliceRatio((float)currentSkillCost / MAX_GAUGE_MOONLIGHT, 1.f);

	// ���� ������ ��ȭ
	if (currentSkillCost >= moonlight_gauge_skill->GetCost()) state = OBJECT_STATE::MOONLIGHT_GAUGE_ABLED;
	else state = OBJECT_STATE::MOONLIGHT_GAUGE_DISABLED;
	moonlight_gauge_state_icon->GetComponent<FSM>()->ChangeState(state);
}

// �ֽ��ϴ� ������ ��ȯ
void Level_Boss_Will_Phase1::SummonWatchingEyes(int param)
{
	if (param == 0)
	{
		watchingEyes[0]->UseSkill();
	}
	else if (param == 1)
	{
		watchingEyes[1]->UseSkill();
	}
	else if (param == 2)
	{
		watchingEyes[2]->UseSkill();
	}
	else if (param == 3)
	{
		watchingEyes[0]->UseSkill();
		watchingEyes[1]->UseSkill();
	}
	else if (param == 4)
	{
		watchingEyes[0]->UseSkill();
		watchingEyes[2]->UseSkill();
	}
	else if (param == 5)
	{
		watchingEyes[1]->UseSkill();
		watchingEyes[2]->UseSkill();
	}
	else if (param == 6)
	{
		watchingEyes[0]->UseSkill();
		watchingEyes[1]->UseSkill();
		watchingEyes[2]->UseSkill();
	}
}

// �Ŵ�Ź� �ٸ� ��ȯ
void Level_Boss_Will_Phase1::SummonSpiderLegs(int param)
{
	if (param == 0)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[1]->UseSkill();
	}
	else if (param == 1)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[2]->UseSkill();
	}
	else if (param == 2)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 3)
	{
		spiderLegs[1]->UseSkill();
		spiderLegs[2]->UseSkill();
	}
	else if (param == 4)
	{
		spiderLegs[1]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 5)
	{
		spiderLegs[2]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 6)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[1]->UseSkill();
		spiderLegs[2]->UseSkill();
	}
	else if (param == 7)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[1]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 8)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[2]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 9)
	{
		spiderLegs[1]->UseSkill();
		spiderLegs[2]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
	else if (param == 10)
	{
		spiderLegs[0]->UseSkill();
		spiderLegs[1]->UseSkill();
		spiderLegs[2]->UseSkill();
		spiderLegs[3]->UseSkill();
	}
}