#pragma once
#include "AliveObject.h"

class Player;

// ���
constexpr auto DEFAULT_DETECT_RANGE = 500.f;	// �ִ� ���� ����
constexpr auto MAX_TRACE_DISTANCE = 150.f;		// ������ ���ߴ� �÷��̾���� �Ÿ�

// ���� Ŭ���� 
class Monster : public AliveObject
{
private:
	static Player* player;

private:
	const float detectRange = DEFAULT_DETECT_RANGE;	// �÷��̾� ���� ���� (������ ����)

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