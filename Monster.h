#pragma once
#include "AliveObject.h"

constexpr auto DEFAULT_DETECT_RANGE = 500.f;
constexpr auto MAX_TRACE_DISTANCE = 150.f;

// ���� Ŭ���� 
class Monster : public AliveObject
{
private:
	static GameObject* player;

private:
	const int detectRange;	// �÷��̾� ���� ���� (������ ����)

public:
	Monster(const wstring& name, Vec2 pos, Vec2 scale=DEFAULT_OBJECT_SCALE, int detectRange=DEFAULT_DETECT_RANGE);
	Monster(const Monster& origin);
	~Monster();
	virtual Monster* Clone() override { return new Monster(*this); }

	int GetDetectRange() { return detectRange; }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

	bool DetectPlayer();
	bool Trace();
};