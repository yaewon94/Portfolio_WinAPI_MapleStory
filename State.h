#pragma once
#include "Entity.h"

class FSM;

// ������Ʈ ����
enum class OBJECT_STATE
{
	IDLE
};

// ������Ʈ�� ���¸� ��Ÿ���� Ŭ����
// [abstract class]
class State : public Entity
{
	friend class FSM;

	NO_CSTR_COPY_ASSIGN(State);

private:
	FSM* fsm;
	OBJECT_STATE type;

protected:
	State(FSM& fsm, OBJECT_STATE type);
	~State();

	virtual void Enter() = 0;
	virtual void Stay() = 0;
	virtual void Exit() = 0;
};