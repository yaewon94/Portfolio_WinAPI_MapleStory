#pragma once
#include "State.h"

class JumpState : public State
{
	NO_CSTR_COPY_ASSIGN(JumpState);

public:
	JumpState();
	~JumpState();

	virtual void Enter() override;
	virtual void Stay() override {}
	virtual void Exit() override {}
};