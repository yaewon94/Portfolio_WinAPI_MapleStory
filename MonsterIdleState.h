#pragma once
#include "State.h"

class Monster;

class MonsterIdleState : public State
{
private:
	Monster* me;

public:
	MonsterIdleState();
	MonsterIdleState(const MonsterIdleState& origin);
	~MonsterIdleState();
	virtual MonsterIdleState* Clone() override { return new MonsterIdleState(*this); }

	virtual void Init() override;

	virtual void Enter() override {}
	virtual void Stay() override;
	virtual void Exit() override {}
};