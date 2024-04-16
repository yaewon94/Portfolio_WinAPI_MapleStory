#pragma once
#include "Component.h"
#include "GameObject.h"

// 오브젝트의 물리 충돌 처리를 위한 컴포넌트
class Collider final : public Component
{
private:
	Vec2<float> offset;	// 게임 오브젝트의 좌표를 기준으로 한 로컬좌표
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