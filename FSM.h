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

private:
	State* FindState(OBJECT_STATE type);
};

// ���� �߰�
inline void FSM::AddState(State& state)
{
	if (FindState(state.type) == nullptr) stateMap.insert(make_pair(state.type, &state));
	else Log(LOG_TYPE::LOG_ERROR, L"�̹� �߰��� �����Դϴ�");
}

// ���� ����
inline void FSM::ChangeState(OBJECT_STATE type)
{
	auto state = FindState(type);
	if (state != nullptr) curState = state;
	else Log(LOG_TYPE::LOG_ERROR, L"�����Ϸ��� ���°� �����ϴ�");
}
// ���� ã��
inline State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}