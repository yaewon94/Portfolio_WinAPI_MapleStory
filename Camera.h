#pragma once
#include "Entity.h"

class GameObject;

class Camera final : public Entity
{
	friend class Level; // [check]

private:
	Vec2 diff; // 실제 좌표와 렌더링 좌표와의 차이
	Vec2 resolution;
	GameObject* player;

	Camera();
	Camera(const Camera& origin) = delete;
	~Camera();

	virtual void Init() override;
	virtual void Tick() override {}
	virtual void FinalTick() override;

public:
	Vec2 GetRenderPos(Vec2& realPos) const { return realPos - diff; }
};