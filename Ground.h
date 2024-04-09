#pragma once
#include "GameObject.h"

// 발판 오브젝트
class Ground final : public GameObject
{
public:
	Ground(Vec2 pos, Vec2 scale);
	Ground(const Ground& origin);
	~Ground();
	virtual Ground* Clone() override { return new Ground(*this); }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};