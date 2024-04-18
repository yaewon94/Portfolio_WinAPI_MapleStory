#pragma once
#include "Entity.h"

class FSM;

// 오브젝트의 상태를 나타내는 클래스
// [abstract class]
class State : public Entity
{
	friend class FSM;

private:
	FSM* fsm;
	OBJECT_STATE type;
	const float CoolDown;		// 해당 상태 종료 후, 다시 해당 상태가 되기 위해 필요한 쿨타임
	const float Duration;		// 상태 지속시간
	float time = 0.f;			// 상태가 시작된 후 경과한 시간

private:
	void SetFsm(FSM& fsm) { this->fsm = &fsm; }

protected:
	float exitTime = 0.f;		// 상태 종료 시간

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