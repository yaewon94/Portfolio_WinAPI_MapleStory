#pragma once
#include "GameObject.h"

constexpr auto DEFAULT_DETECT_RANGE = 500.f;

// ���� Ŭ���� 
class Monster : public GameObject
{
private:
	static GameObject* player;

private:
	const float detectRange;	// �÷��̾� ���� ���� (������ ����)

public:
	Monster(const wstring& name, Vec2<float> pos, Vec2<int> scale=DEFAULT_OBJECT_SCALE, float detectRange=DEFAULT_DETECT_RANGE);
	Monster(const Monster& origin);
	~Monster();
	virtual Monster* Clone() override { return new Monster(*this); }

	float GetDetectRange() { return detectRange; }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

	bool DetectPlayer();
};