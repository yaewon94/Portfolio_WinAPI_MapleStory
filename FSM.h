#pragma once
#include "Component.h"
#include "State.h"

// ������Ʈ�� �� ���¸� ó���ϴ� ������Ʈ
class FSM final : public Component
{
private:
	map<OBJECT_STATE, State*> stateMap;
	State* curState;

public:
	FSM(GameObject& owner);
	FSM(const FSM& origin);
	~FSM();
	virtual FSM* Clone() override { return new FSM(*this); }

	virtual void Init() override;

	void AddState(State& state);
	void ChangeState(OBJECT_STATE type);
	OBJECT_STATE GetCurrentState() const { return curState->type; }

private:
	State* FindState(OBJECT_STATE type);
};