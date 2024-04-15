#pragma once
#include "GameObject.h"

// 벽 오브젝트
// Background, Ground, Wall 클래스 분리할 필요 없었는데, 시간없으니 이번엔 그냥 놔둠
class Wall final : public GameObject
{
public:
	Wall(Vec2<float> pos, Vec2<int> scale);
	Wall(const Wall& origin);
	~Wall();
	virtual Wall* Clone() override { return new Wall(*this); }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};