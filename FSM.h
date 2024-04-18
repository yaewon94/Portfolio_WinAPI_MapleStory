#pragma once
#include "Component.h"
#include "State.h"

// ������Ʈ�� �� ���¸� ó���ϴ� ������Ʈ
class FSM final : public Component
{
private:
	//const OBJECT_STATE DefaultStateType;
	OBJECT_STATE DefaultStateType = OBJECT_STATE::NONE;	// GameObject::AddComponent<T>() ���� ��� �ʱ�ȭ ��������. ������ ��¿������ ����� �ƴ϶� ������ ����

private:
	map<OBJECT_STATE, State*> stateMap;
	OBJECT_STATE curStateType;
	State* curState;

public:
	//FSM(GameObject& owner, OBJECT_STATE DefaultState);
	FSM(GameObject& owner);
	FSM(const FSM& origin);
	~FSM();
	virtual FSM* Clone() override { return new FSM(*this); }

	virtual void Init() override;
	virtual void FinalTick() override;

	OBJECT_STATE GetDefaultState() const { return DefaultStateType; }
	void SetDefaultState(OBJECT_STATE type) { DefaultStateType = type; }
	OBJECT_STATE GetCurrentState() const { return curStateType; }

	void AddState(State& state);
	void ChangeState(OBJECT_STATE type);

private:
	State* FindState(OBJECT_STATE type);
};