#pragma once
#include "Level.h"

class ActiveSkill;
class SkillSummonerObject;
class GameObject;
class Monster;

// [임시 하드코딩] 상수
#define MOONLIGHT_GAUGE_SCALE Vec2(150, 150)	// 달빛게이지 크기
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// 달빛게이지 회복 주기 (초)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// 한번에 회복되는 달빛게이지량

constexpr auto COUNT_PER_SUMMON = 2;	// 한번에 소환되는 윌의 마릿수
constexpr auto WILL_MAX_HP = 1000;		// 윌 (1마리당) 최대체력

constexpr auto INTERVAL_SUMMON_MONSTER = 5.f;	// 맵 자체 몬스터가 등장하는 주기 (초)
constexpr auto COUNT_WATCHING_EYES = 3;			// 주시하는 눈동자 최대 마릿수
constexpr auto COUNT_SPIDER_LEGS = 4;			// 거미다리 최대 마릿수

// 윌 1페이즈
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	// 보스레이드 성공 여부
	bool isSucceed = false;

	// 달빛게이지
	ActiveSkill* moonlight_gauge_skill = nullptr;
	GameObject* moonlight_gauge_ratio_obj = nullptr;
	GameObject* moonlight_gauge_state_icon = nullptr;
	//Texture* textureBufferTest;

	// 윌 오브젝트
	Monster* bossWill_blue = nullptr;
	Monster* bossWill_pupple = nullptr;
	// 윌 체력게이지
	const int WillHP_max_total = WILL_MAX_HP * COUNT_PER_SUMMON;	// 윌 전체체력 MAX값
	int willHP_cur_total = WillHP_max_total;						// 윌 전체체력 현재값
	GameObject* willHP_gauge_total = nullptr;						// 윌 전체체력바 게이지 UI

	// 윌 1페이지 자체몹, 자체스킬
	array<SkillSummonerObject*, COUNT_WATCHING_EYES> watchingEyes;	// 주시하는 눈동자
	array<SkillSummonerObject*, COUNT_SPIDER_LEGS> spiderLegs;		// 거미다리 내려찍기

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