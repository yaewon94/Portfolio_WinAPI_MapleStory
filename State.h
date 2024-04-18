#pragma once
#include "Entity.h"

class FSM;

// ������Ʈ�� ���¸� ��Ÿ���� Ŭ����
// [abstract class]
class State : public Entity
{
	friend class FSM;

private:
	FSM* fsm;
	OBJECT_STATE type;
	const float CoolDown;		// �ش� ���� ���� ��, �ٽ� �ش� ���°� �Ǳ� ���� �ʿ��� ��Ÿ��
	const float Duration;		// ���� ���ӽð�
	float time = 0.f;			// ���°� ���۵� �� ����� �ð�

private:
	void SetFsm(FSM& fsm) { this->fsm = &fsm; }

protected:
	float exitTime = 0.f;		// ���� ���� �ð�

protected:
	State(OBJECT_STATE type, float coolDown=0.f, float Duration=0.f);
	State(const State& origin);
	~State();
	virtual State* Clone() = 0;

	FSM& GetFsm() { return *fsm; }

	virtual void Init() {}

	virtual void Enter() = 0;
	virtual void Stay();
	virtual void Exit() = 0;
};