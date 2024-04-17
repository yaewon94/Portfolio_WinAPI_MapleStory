#pragma once
#include "AliveObject.h"

class Player;

// 상수
constexpr auto DEFAULT_DETECT_RANGE = 500.f;	// 최대 감지 범위
constexpr auto MAX_TRACE_DISTANCE = 150.f;		// 추적을 멈추는 플레이어와의 거리

// 몬스터 클래스 
class Monster : public AliveObject
{
private:
	static Player* player;

private:
	const float detectRange = DEFAULT_DETECT_RANGE;	// 플레이어 감지 범위 (반지름 기준)

public:
	Monster(const wstring& name, int MaxHP);
	Monster(const Monster& origin);
	~Monster();
	virtual Monster* Clone() override { return new Monster(*this); }

	float GetDetectRange() { return detectRange; }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

	bool DetectPlayer();
	bool Trace();
};