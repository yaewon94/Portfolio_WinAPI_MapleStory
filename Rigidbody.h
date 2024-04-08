#pragma once
#include "Component.h"

// ������Ʈ�� ���������� �����ϱ� ���� ������Ʈ
class Rigidbody final : public Component
{
private:
	float mass;
	Vec2 force;
	Vec2 velocity;
	bool useGravity = false;

public:
	Rigidbody(GameObject& owner, float mass=1.f);
	Rigidbody(const Rigidbody& origin);
	~Rigidbody();
	virtual Rigidbody* Clone() override { return new Rigidbody(*this); }

	void AddForce(Vec2 force) { velocity = force; }
	void UseGravity(bool flag) { useGravity = flag; }

	virtual void FinalTick() override;
};