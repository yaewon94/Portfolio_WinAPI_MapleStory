#pragma once
#include "Component.h"
#include "State.h"

// 오브젝트의 각 상태를 처리하는 컴포넌트
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

// 상태 추가
inline void FSM::AddState(State& state)
{
	if (FindState(state.type) == nullptr) stateMap.insert(make_pair(state.type, &state));
	else Log(LOG_TYPE::LOG_ERROR, L"이미 추가된 상태입니다");
}

// 상태 변경
inline void FSM::ChangeState(OBJECT_STATE type)
{
	auto state = FindState(type);
	if (state != nullptr) curState = state;
	else Log(LOG_TYPE::LOG_ERROR, L"변경하려는 상태가 없습니다");
}
// 상태 찾기
inline State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}