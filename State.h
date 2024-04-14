#pragma once
#include "Entity.h"

class FSM;

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
	State(OBJECT_STATE type);
	~State();
	virtual State* Clone() override { return nullptr; }

	FSM& GetFsm() { return *fsm; }

	virtual void Init() {}

	virtual void Enter() = 0;
	virtual void Stay() = 0;
	virtual void Exit() = 0;
};