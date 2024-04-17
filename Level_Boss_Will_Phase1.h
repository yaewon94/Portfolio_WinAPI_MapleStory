#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;

// 상수
#define GAUGE_POS Vec2(120.f, 200.f)			// 달빛게이지 좌표
#define GAUGE_SCALE Vec2(150, 150)				// 달빛게이지 크기
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// 달빛게이지 회복 주기 (초)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// 한번에 회복되는 달빛게이지량

// 윌 1페이즈
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	ActiveSkill* gauge_skill = nullptr;
	GameObject* gauge_percent = nullptr; 
	GameObject* gauge_state = nullptr;
	//Texture* textureBufferTest;

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