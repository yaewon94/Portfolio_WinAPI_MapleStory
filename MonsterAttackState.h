#pragma once
#include "State.h"

class Monster;

// ���� ���ݻ���
class MonsterAttackState : public State
{
private:
	Monster* me;

public:
	MonsterAttackState(float coolDown);
	MonsterAttackState(const MonsterAttackState& origin);
	~MonsterAttackState();
	virtual MonsterAttackState* Clone() override { return new MonsterAttackState(*this); }

	virtual void Init() override;

	virtual void Enter() override;
	virtual void Stay() override {}
	virtual void Exit() override;
};