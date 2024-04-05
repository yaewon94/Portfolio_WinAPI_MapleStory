#pragma once
#include "Level.h"

class GameObject;

// ���� ���� Ŭ����
class LevelManager final
{
	SINGLETON(LevelManager);

private:
	LEVEL_TYPE level_ID;
	Level* curLevel;

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

	void ChangeLevel(LEVEL_TYPE level);
	GameObject* FindObject(LAYER_TYPE layer);
	Camera* GetMainCamera() { return curLevel->mainCamera; }
};