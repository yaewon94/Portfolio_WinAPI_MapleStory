#pragma once
#include "Level.h"

class GameObject;

// 상수
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// 한번에 회복되는 달빛게이지량
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// 달빛게이지 회복 주기 (초)

// 윌 1페이즈
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	GameObject* gauge_moonlight;

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