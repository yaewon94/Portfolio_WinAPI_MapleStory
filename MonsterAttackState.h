#pragma once
#include "State.h"

class Monster;

// 몬스터 공격상태
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