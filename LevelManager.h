#pragma once

class Level;

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

	void ChangeLevel(const LEVEL_TYPE level);
};