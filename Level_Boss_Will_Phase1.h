#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;
class Monster;

// [�ӽ� �ϵ��ڵ�] ���
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)	// �޺������� ũ��
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// �޺������� ȸ�� �ֱ� (��)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// �ѹ��� ȸ���Ǵ� �޺���������

constexpr auto COUNT_PER_SUMMON = 2;	// �ѹ��� ��ȯ�Ǵ� ���� ������
constexpr auto WILL_MAX_HP = 100;		// �� (1������) �ִ�ü��

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

private:
	NO_CSTR_COPY_ASSIGN(Level_Boss_Will_Phase1);
	Level_Boss_Will_Phase1();
	~Level_Boss_Will_Phase1();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void FinalTick() override;

public:
	virtual void OnAlertBossHpZero() override;
	virtual void OnChangeGaugePercent(int currentSkillCost) override;
};