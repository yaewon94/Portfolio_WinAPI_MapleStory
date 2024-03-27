#pragma once
#include "Level.h"

// ���� ���� Ŭ����
class LevelManager final
{
	SINGLETON(LevelManager);

private:
	LEVEL_TYPE level_ID;
	Level* curLevel;

public:
	Level& GetCurrentLevel() { return *curLevel; }

	void Init();
	void Tick();
	void FinalTick();
	void Render();

	void ChangeLevel(const LEVEL_TYPE level);
};