#pragma once
#include "Level.h"

class ActiveSkill;
class SkillSummonerObject;
class GameObject;
class Monster;

// [�ӽ� �ϵ��ڵ�] ���
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)	// �޺������� ũ��
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// �޺������� ȸ�� �ֱ� (��)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// �ѹ��� ȸ���Ǵ� �޺���������

constexpr auto COUNT_PER_SUMMON = 2;	// �ѹ��� ��ȯ�Ǵ� ���� ������
constexpr auto WILL_MAX_HP = 1000;		// �� (1������) �ִ�ü��

constexpr auto INTERVAL_SUMMON_MONSTER = 5.f;	// �� ��ü ���Ͱ� �����ϴ� �ֱ� (��)
constexpr auto COUNT_WATCHING_EYES = 3;			// �ֽ��ϴ� ������ �ִ� ������
constexpr auto COUNT_SPIDER_LEGS = 4;			// �Ź̴ٸ� �ִ� ������

// �� 1������
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	// �������̵� ���� ����
	bool isSucceed = false;

	// �޺�������
	ActiveSkill* moonlight_gauge_skill = nullptr;
	GameObject* moonlight_gauge_ratio_obj = nullptr;
	GameObject* moonlight_gauge_state_icon = nullptr;
	//Texture* textureBufferTest;

	// �� ������Ʈ
	Monster* bossWill_blue = nullptr;
	Monster* bossWill_pupple = nullptr;
	// �� ü�°�����
	const int WillHP_max_total = WILL_MAX_HP * COUNT_PER_SUMMON;	// �� ��üü�� MAX��
	int willHP_cur_total = WillHP_max_total;						// �� ��üü�� ���簪
	GameObject* willHP_gauge_total = nullptr;						// �� ��üü�¹� ������ UI

	// �� 1������ ��ü��, ��ü��ų
	array<SkillSummonerObject*, COUNT_WATCHING_EYES> watchingEyes;	// �ֽ��ϴ� ������
	array<SkillSummonerObject*, COUNT_SPIDER_LEGS> spiderLegs;		// �Ź̴ٸ� �������

private:
	NO_CSTR_COPY_ASSIGN(Level_Boss_Will_Phase1);
	Level_Boss_Will_Phase1();
	~Level_Boss_Will_Phase1();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Tick() override;
	virtual void FinalTick() override;

public:
	virtual void OnAlertBossHpZero() override;
	virtual void OnChangeGaugePercent(int currentSkillCost) override;

private:
	void SummonWatchingEyes(int param);
	void SummonSpiderLegs(int param);
};