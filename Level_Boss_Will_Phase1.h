#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;

// [임시 하드코딩] 상수
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)	// 달빛게이지 크기
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// 달빛게이지 회복 주기 (초)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// 한번에 회복되는 달빛게이지량

constexpr auto COUNT_PER_SUMMON = 2;	// 한번에 소환되는 윌의 마릿수
constexpr auto WILL_MAX_HP = 100;		// 윌 (1마리당) 최대체력

// 윌 1페이즈
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	// 달빛게이지
	ActiveSkill* moonlight_gauge_skill = nullptr;
	GameObject* moonlight_gauge_ratio_obj = nullptr; 
	GameObject* moonlight_gauge_state_icon = nullptr;
	//Texture* textureBufferTest;

	// 윌 체력게이지
	const int WillHP_max_total = WILL_MAX_HP * COUNT_PER_SUMMON;	// 윌 전체체력 MAX값
	int willHP_cur_total = WillHP_max_total;						// 윌 전체체력 현재값
	GameObject* willHP_gauge_total = nullptr;						// 윌 전체체력바 게이지 UI

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