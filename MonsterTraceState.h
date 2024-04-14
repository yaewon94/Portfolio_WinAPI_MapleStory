#pragma once
#include "State.h"

class Monster;

class MonsterTraceState : public State
{
	NO_CSTR_COPY_ASSIGN(MonsterTraceState);

private:
	Monster* me;

public:
	MonsterTraceState();
	~MonsterTraceState();

	virtual void Init() override;

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};