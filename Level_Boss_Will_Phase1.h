#pragma once
#include "Level.h"

// ¿™ 1∆‰¿Ã¡Ó
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	NO_CSTR_COPY_ASSIGN(Level_Boss_Will_Phase1);
	Level_Boss_Will_Phase1();
	~Level_Boss_Will_Phase1();

	virtual void Enter() override;
	virtual void Exit() override;
};