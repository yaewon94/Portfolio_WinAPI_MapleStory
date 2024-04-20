#include "PCH.h"
#include "DeadBeforeState.h"
#include "Collider.h"
#include "FSM.h"
#include "GameObject.h"

// 생성자
DeadBeforeState::DeadBeforeState(float Duration) 
	: State(OBJECT_STATE::DEAD_BEFORE, OBJECT_STATE::DEAD, 0.f, Duration)
{
}

// 복사 생성자
DeadBeforeState::DeadBeforeState(const DeadBeforeState& origin) : State(origin)
{
}

// 소멸자
DeadBeforeState::~DeadBeforeState()
{
}

// 상태 진입
void DeadBeforeState::Enter()
{
	// 콜라이더 비활성화
	Collider* collider = GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(false);
}