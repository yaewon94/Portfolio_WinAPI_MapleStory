#pragma once
#include "Component.h"
#include "GameObject.h"

// 오브젝트의 물리 충돌 처리를 위한 컴포넌트
class Collider final : public Component
{
private:
	Vec2 offset;	// 게임 오브젝트의 좌표를 기준으로 한 로컬좌표
	Vec2 scale;

public:
	Collider(GameObject& owner);
	Collider(const Collider& origin);
	~Collider();
	virtual Collider* Clone() override { return new Collider(*this); }

	Vec2 GetPos() { return offset + GetOwner()->GetPos(); }
	Vec2 GetScale() { return scale; }
	void SetScale(Vec2 scale) { this->scale = scale; }
};