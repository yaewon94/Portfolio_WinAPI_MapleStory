#pragma once
#include "Component.h"
#include "GameObject.h"

// ������Ʈ�� ���� �浹 ó���� ���� ������Ʈ
class Collider final : public Component
{
private:
	Vec2 offset;	// ���� ������Ʈ�� ��ǥ�� �������� �� ������ǥ
	Vec2 scale;

public:
	Collider(GameObject& owner);
	Collider(const Collider& origin);
	~Collider();
	virtual Collider* Clone() override { return new Collider(*this); }

	Vec2 GetPos() { return offset + GetOwner()->GetPos(); }
	Vec2 GetRenderPos();
	Vec2 GetScale() const { return scale; }

	void SetOffset(Vec2 offset) { this->offset = offset; }
	void SetScale(Vec2 scale) { this->scale = scale; }

	virtual void Init() override;
};