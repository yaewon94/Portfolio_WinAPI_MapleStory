#pragma once
#include "Level.h"

// 테스트용 레벨 클래스
class Level_Test final : public Level
{
	friend class LevelManager;

private:
	NO_CSTR_COPY_ASSIGN(Level_Test);
	Level_Test();
	~Level_Test();

	virtual void Enter() override;
	virtual void Exit() override;
};