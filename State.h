#pragma once
#include "Entity.h"

class FSM;

// 오브젝트 상태
enum class OBJECT_STATE
{
	IDLE
};

// 오브젝트의 상태를 나타내는 클래스
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