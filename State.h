#pragma once
#include "Entity.h"

class FSM;

// ������Ʈ�� ���¸� ��Ÿ���� Ŭ����
// [abstract class]
class State : public Entity
{
	friend class FSM;

	NO_CSTR_COPY_ASSIGN(State);

private:
	FSM* fsm;
	OBJECT_STATE type;
	const float CoolDown;		// �ش� ���� ���� ��, �ٽ� �ش� ���°� �Ǳ� ���� �ʿ��� ��Ÿ��

protected:
	float exitTime = 0.f;		// ���� ���� �ð�

protected:
	State(OBJECT_STATE type, float coolDown=0.f);
	~State();

	FSM& GetFsm() { return *fsm; }

	virtual void Init() {}

	virtual void Enter() = 0;
	virtual void Stay() = 0;
	virtual void Exit() = 0;
};