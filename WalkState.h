#pragma once
#include "State.h"

class WalkState : public State
{
	NO_CSTR_COPY_ASSIGN(WalkState);

public:
	WalkState();
	~WalkState();

	virtual void Enter() override;
	virtual void Stay() override {}
	virtual void Exit() override {}
};