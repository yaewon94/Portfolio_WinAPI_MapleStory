#include "PCH.h"
#include "DeadState.h"
#include "FSM.h"
#include "Collider.h"
#include "GameObject.h"

// 생성자
DeadState::DeadState(float Duration) : State(OBJECT_STATE::DEAD, 0.f, Duration)
{
}

// 복사 생성자
DeadState::DeadState(const DeadState& origin) : State(origin)
{
}

// 소멸자
DeadState::~DeadState()
{
}

// 상태 진입
void DeadState::Enter()
{
	// 콜라이더 비활성화
	Collider* collider =GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(false);
}

// 상태 종료
void DeadState::Exit()
{
	// 콜라이더 활성화
	Collider* collider = GetFsm().GetOwner()->GetComponent<Collider>();
	if (collider != nullptr) collider->SetActive(true);
}