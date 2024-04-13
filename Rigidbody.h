#pragma once
#include "Component.h"

// 오브젝트를 물리적으로 제어하기 위한 컴포넌트
class Rigidbody final : public Component
{
private:
	float mass;
	Vec2<float> force;
	Vec2<float> velocity;
	bool useGravity = true;

public:
	Rigidbody(GameObject& owner, float mass=1.f);
	Rigidbody(const Rigidbody& origin);
	~Rigidbody();
	virtual Rigidbody* Clone() override { return new Rigidbody(*this); }

	void AddForce(Vec2<float> force) { velocity = force; }
	void UseGravity(bool flag) { useGravity = flag; }

	virtual void FinalTick() override;
};