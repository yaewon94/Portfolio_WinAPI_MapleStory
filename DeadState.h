#pragma once
#include "State.h"

// 체력이 0이 되었을 때 전환되는 상태
// [abstract class]
class DeadState : public State
{
protected:
	DeadState(float Duration=0.f);
	DeadState(const DeadState& origin);
	~DeadState();

	virtual void Enter() override;
	virtual void Exit() override;
};