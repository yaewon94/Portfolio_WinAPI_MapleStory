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
	const float CoolDown;		// 해당 상태 종료 후, 다시 해당 상태가 되기 위해 필요한 쿨타임

protected:
	float exitTime = 0.f;		// 상태 종료 시간

protected:
	State(OBJECT_STATE type, float coolDown=0.f);
	~State();

	FSM& GetFsm() { return *fsm; }

	virtual void Init() {}

	virtual void Enter() = 0;
	virtual void Stay() = 0;
	virtual void Exit() = 0;
};