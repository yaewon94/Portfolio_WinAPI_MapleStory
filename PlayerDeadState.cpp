#include "PCH.h"
#include "PlayerDeadState.h"
#include "UIManager.h"

// 생성자
PlayerDeadState::PlayerDeadState() : DeadState()
{
}

// 복사 생성자
PlayerDeadState::PlayerDeadState(const DeadState& origin) : DeadState(origin)
{
}

// 소멸자
PlayerDeadState::~PlayerDeadState()
{
}

// 상태 진입
void PlayerDeadState::Enter()
{
	UIManager::GetInstance().ShowUI("AlertBox_Revival");
}

// 매 프레임마다 호출
void PlayerDeadState::Stay()
{
	// State::Stay() 사용 안함

	// TODO : 플레이어 오브젝트가 원을 그리면서 움직이게 함
}