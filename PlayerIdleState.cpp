#include "PCH.h"
#include "PlayerIdleState.h"

// 생성자
PlayerIdleState::PlayerIdleState()
{
}

// 소멸자
PlayerIdleState::~PlayerIdleState()
{
}

// 상태 진입
void PlayerIdleState::Enter()
{
	IdleState::Enter();
}