#include "PCH.h"
#include "PlayerDeadState.h"
#include "UIManager.h"

// ������
PlayerDeadState::PlayerDeadState() : DeadState()
{
}

// ���� ������
PlayerDeadState::PlayerDeadState(const DeadState& origin) : DeadState(origin)
{
}

// �Ҹ���
PlayerDeadState::~PlayerDeadState()
{
}

// ���� ����
void PlayerDeadState::Enter()
{
	UIManager::GetInstance().ShowUI("AlertBox_Revival");
}

// �� �����Ӹ��� ȣ��
void PlayerDeadState::Stay()
{
	// State::Stay() ��� ����

	// TODO : �÷��̾� ������Ʈ�� ���� �׸��鼭 �����̰� ��
}