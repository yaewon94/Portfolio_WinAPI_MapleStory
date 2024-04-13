#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(const wstring& name, Vec2<float> pos, Vec2<int> scale);
	Monster(const Monster& origin);
	~Monster();
	virtual Monster* Clone() override { return new Monster(*this); }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};