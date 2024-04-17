#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;

// [�ӽ� �ϵ��ڵ�] ���
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)			// �޺������� ũ��
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// �޺������� ȸ�� �ֱ� (��)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// �ѹ��� ȸ���Ǵ� �޺���������
constexpr auto WILL_MAX_HP = 1000;	// �� �ִ�ü��

// �� 1������
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	ActiveSkill* moonlight_gauge_skill = nullptr;
	GameObject* moonlight_gauge_ratio_obj = nullptr; 
	GameObject* moonlight_gauge_state_icon = nullptr;
	//Texture* textureBufferTest;

	GameObject* willHP_gauge_total = nullptr;

private:
	NO_CSTR_COPY_ASSIGN(Level_Boss_Will_Phase1);
	Level_Boss_Will_Phase1();
	~Level_Boss_Will_Phase1();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void FinalTick() override;

public:
	virtual void OnChangeGaugePercent(int currentSkillCost) override;
};