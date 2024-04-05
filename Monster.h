#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(const wstring& name, Vec2 pos, Vec2 scale);
	Monster(const Monster& origin);
	~Monster();
	virtual Monster* Clone() override { return new Monster(*this); }

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};