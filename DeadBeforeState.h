#pragma once
#include "State.h"

// ������ �ױ� ���� ����
// �ִϸ��̼� ��ȯ�� ���� �δ� �뵵
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