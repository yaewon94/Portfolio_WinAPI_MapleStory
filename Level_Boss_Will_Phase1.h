#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;

// [임시 하드코딩] 상수
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)			// 달빛게이지 크기
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// 달빛게이지 회복 주기 (초)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// 한번에 회복되는 달빛게이지량
constexpr auto WILL_MAX_HP = 1000;	// 윌 최대체력

// 윌 1페이즈
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