#pragma once
#include "State.h"

// [abstract class]
class IdleState : public State
{
	NO_CSTR_COPY_ASSIGN(IdleState);

public:
	IdleState();
	~IdleState();

	virtual void Enter() override;
	virtual void Stay() = 0;
	virtual void Exit() = 0;
};