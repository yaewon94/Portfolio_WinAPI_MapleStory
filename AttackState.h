#pragma once
#include "State.h"

class AttackState : public State
{
	NO_CSTR_COPY_ASSIGN(AttackState);

public:
	AttackState();
	~AttackState();

	virtual void Enter() override;
	virtual void Stay() override {}
	virtual void Exit() override;
};