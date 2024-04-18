#pragma once
#include "State.h"

// ü���� 0�� �Ǿ��� �� ��ȯ�Ǵ� ����
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