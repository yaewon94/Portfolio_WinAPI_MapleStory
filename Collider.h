#pragma once
#include "Component.h"
#include "GameObject.h"

// ������Ʈ�� ���� �浹 ó���� ���� ������Ʈ
class Collider final : public Component
{
private:
	Vec2<float> offset;	// ���� ������Ʈ�� ��ǥ�� �������� �� ������ǥ
	Vec2<int> scale;

public:
	Collider(GameObject& owner);
	Collider(const Collider& origin);
	~Collider();
	virtual Collider* Clone() override { return new Collider(*this); }

	Vec2<float> GetPos() { return offset + GetOwner()->GetRealPos(); }
	Vec2<float> GetRenderPos();
	Vec2<int> GetScale() const { return scale; }

	void SetOffset(Vec2<float> offset) { this->offset = offset; }
	void SetScale(Vec2<int> scale) { this->scale = scale; }

	virtual void Init() override;
};