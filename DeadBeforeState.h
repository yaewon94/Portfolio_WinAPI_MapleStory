#pragma once
#include "State.h"

// 완전히 죽기 전의 상태
// 애니메이션 전환에 텀을 두는 용도
class DeadBeforeState final : public State
{
public:
	DeadBeforeState(float Duration=0.f);
	DeadBeforeState(const DeadBeforeState& origin);
	~DeadBeforeState();
	virtual DeadBeforeState* Clone() { return new DeadBeforeState(*this); }

	virtual void Enter() override;
	virtual void Exit() override {}
};