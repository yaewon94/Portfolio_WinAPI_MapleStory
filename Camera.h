#pragma once
#include "Entity.h"

class GameObject;

class Camera final : public Entity
{
	friend class Level; // [check]

	NO_CSTR_COPY_ASSIGN(Camera);
private:
	Vec2<float> diff; // 실제 좌표와 렌더링 좌표와의 차이
	Vec2<int> resolution;
	GameObject* player;

	Camera();
	~Camera();
	virtual Camera* Clone() { return nullptr; }

	void Init();
	void FinalTick();

public:
	Vec2<float> GetRenderPos(Vec2<float> realPos) { return realPos - diff; }
};