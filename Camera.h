#pragma once
#include "Entity.h"

class GameObject;
class Map;

class Camera final : public Entity
{
	friend class Level; // [check]

	NO_CSTR_COPY_ASSIGN(Camera);
private:
	Vec2<float> diff = Vec2((float)INT_MIN, (float)INT_MIN); // 실제 좌표와 렌더링 좌표와의 차이
	Vec2<int> resolution;
	GameObject* player;
	Map* currentMap;

	Camera();
	~Camera();

	void Init();
	void FinalTick();

public:
	Vec2<float> GetRenderPos(Vec2<float> realPos) { return realPos - diff; }
	void SetCurrentMap(Map* map);
};