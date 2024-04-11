#pragma once
#include "State.h"

class PlayerIdleState : public State
{
	NO_CSTR_COPY_ASSIGN(PlayerIdleState);

public:
	PlayerIdleState();
	~PlayerIdleState();

	virtual void Enter() override;
	virtual void Stay() override {}
	virtual void Exit() override {}
};