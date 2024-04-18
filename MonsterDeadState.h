#pragma once
#include "DeadState.h"

class MonsterDeadState : public DeadState
{
public:
	MonsterDeadState(float Duration = 0.f);
	MonsterDeadState(const DeadState& origin);
	~MonsterDeadState();
	virtual MonsterDeadState* Clone() { return new MonsterDeadState(*this); }

	virtual void Exit() override;
};