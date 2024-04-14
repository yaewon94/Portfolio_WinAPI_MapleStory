#pragma once
#include "IdleState.h"

class Monster;

class MonsterIdleState : public IdleState
{
	NO_CSTR_COPY_ASSIGN(MonsterIdleState);

private:
	Monster* me;

public:
	MonsterIdleState();
	~MonsterIdleState();

	virtual void Init() override;

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override {}
};