#pragma once
#include "Level.h"

// �׽�Ʈ�� ���� Ŭ����
class Level_Test final : public Level
{
	friend class LevelManager;

private:
	Level_Test();
	Level_Test(const Level_Test&) = delete;
	~Level_Test();

	virtual void Enter() override;
	virtual void Exit() override;
};