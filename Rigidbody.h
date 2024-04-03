#pragma once
#include "Component.h"

// ������Ʈ�� ���������� �����ϱ� ���� ������Ʈ
class Rigidbody final : public Component
{
private:
	int mass;
	Vec2 force;
	Vec2 velocity;
	bool useGravity = false;

public:
	CSTR_COPY_ASSIGN(Rigidbody);
	Rigidbody(GameObject& owner, int mass=1);
	~Rigidbody();
	virtual Rigidbody* Clone() override { return new Rigidbody(*this); }

	void AddForce(Vec2 force);
	void UseGravity(bool flag) { useGravity = flag; }

	virtual void FinalTick() override;
};