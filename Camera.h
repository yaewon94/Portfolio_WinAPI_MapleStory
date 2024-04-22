#pragma once
#include "Entity.h"

class GameObject;
class Map;
class Texture;

// 카메라 클래스
class Camera final : public Entity
{
	friend class Level; // [check]

	NO_CSTR_COPY_ASSIGN(Camera);
private:
	Vec2<float> diff;// = Vec2((float)INT_MIN, (float)INT_MIN); // 실제 좌표와 렌더링 좌표와의 차이
	Vec2<int> resolution;
	GameObject* player;
	Map* currentMap;

	Texture* fadeTex;
	bool useFadeTex = false;
	int curAlpha = 0;
	bool isFadeIn = true;

	Camera();
	~Camera();

	void Init();
	void FinalTick();
	void Render();

public:
	Vec2<float> GetRenderPos(Vec2<float> realPos) { return realPos - diff; }
	void SetCurrentMap(Map* map);
	void SetFadeIn();

private:
	void SetFadeOut();
	void AdjustDiffToMap();
};