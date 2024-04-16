#pragma once
#include "State.h"

class Monster;

class MonsterTraceState : public State
{
private:
	Monster* me;

public:
	MonsterTraceState();
	MonsterTraceState(const MonsterTraceState& origin);
	~MonsterTraceState();
	virtual MonsterTraceState* Clone() override { return new MonsterTraceState(*this); }

	virtual void Init() override;

	virtual void Enter() override {}
	virtual void Stay() override;
	virtual void Exit() override;
};