#pragma once
#include "DeadState.h"

class PlayerDeadState : public DeadState
{
public:
	PlayerDeadState();
	PlayerDeadState(const DeadState& origin);
	~PlayerDeadState();
	virtual PlayerDeadState* Clone() { return new PlayerDeadState(*this); }

	virtual void Enter() override;
	virtual void Stay() override;
};