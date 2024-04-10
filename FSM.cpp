#include "PCH.h"
#include "FSM.h"
#include "State.h"

// 생성자
FSM::FSM(GameObject& owner) : Component(owner), curState(nullptr)
{
}

// 복사 생성자
FSM::FSM(const FSM& origin) : Component(origin), curState(nullptr)
{
}

// 소멸자
FSM::~FSM()
{
	curState = nullptr;
	// [CHECK] State*가 가리키는 객체를 여기서 지워야할지, State에서 처리해야 할지 생각해봐야함
}

// 초기화
void FSM::Init()
{
	// TODO : 상태 추가

	// IDLE 상태를 디폴트로 함
	curState = stateMap.find(OBJECT_STATE::IDLE)->second;
}