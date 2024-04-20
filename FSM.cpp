#include "PCH.h"
#include "FSM.h"
#include "Animator.h"
#include "GameObject.h"
#include "State.h"
#include "TimeManager.h"

// 생성자
FSM::FSM(GameObject& owner) 
	: Component(owner), curState(nullptr)
{
}

// 복사 생성자
FSM::FSM(const FSM& origin) 
	: Component(origin), DefaultStateType(origin.DefaultStateType)
	, curStateType(origin.DefaultStateType), curState(nullptr)
{
	for (auto& pair : origin.stateMap)
	{
		State* state = pair.second->Clone();
		state->SetFsm(*this);
		stateMap.insert(make_pair(pair.first, state));
	}
}

// 소멸자
FSM::~FSM()
{
	curState = nullptr;

	for (auto& state : stateMap)
	{
		if (state.second != nullptr)
		{
			delete state.second;
			nullptr;
		}
	}
}

// 초기화
void FSM::Init()
{
	// 상태 Init()
	for (auto& state : stateMap)
	{
		state.second->Init();
	}

	// 디폴트 상태 전환
	ChangeState(DefaultStateType);
}

// 매 프레임마다 호출
void FSM::FinalTick()
{
	if(curState != nullptr) curState->Stay();
}

// 상태 추가
void FSM::AddState(State& state)
{
	if (FindState(state.type) == nullptr)
	{
		state.fsm = this;
		stateMap.insert(make_pair(state.type, &state));
	}
	else Log(LOG_TYPE::LOG_ERROR, L"이미 추가된 상태입니다");
}

// 상태 변경
void FSM::ChangeState(OBJECT_STATE type)
{
	if (curState != nullptr && curState->type == type)
	{
		Log(LOG_TYPE::LOG_ERROR, L"현재 상태와 변경하려는 상태가 같습니다");
		return;
	}

	// 상태 객체 찾기
	auto state = FindState(type);

	// 객체가 존재할 경우
	if (state != nullptr)
	{
		// 쿨타임 체크
		if ((int)(TimeManager::GetInstance().GetSecond() - state->exitTime) < state->CoolDown)
		{
			Log(LOG_TYPE::LOG_ERROR, L"아직 해당 상태로 변경할 수 없습니다");
			return;
		}

		// 상태 변경
		if(curState != nullptr) curState->Exit();
		curState = state;
		curStateType = type;
		curState->Enter();
		GetOwner()->GetComponent<Animator>()->ChangeAnimation(type);
	}
	// 객체가 존재하지 않을 경우
	// 상태 객체는 없지만 애니메이션 전환 용도
	else
	{
		// 기존 상태가 있는 경우 해제
		if (curState != nullptr) curState->Exit();
		curState = nullptr;
		GetOwner()->GetComponent<Animator>()->ChangeAnimation(type);
		curStateType = type;
	}
}

// 상태 찾기
State* FSM::FindState(OBJECT_STATE type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end()) return iter->second;
	else return nullptr;
}