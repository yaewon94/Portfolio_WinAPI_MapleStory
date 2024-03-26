#pragma once
#include "Level.h"

// 테스트용 레벨 클래스
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