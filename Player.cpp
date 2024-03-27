#include "PCH.h"
#include "Player.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 Scale) : GameObject(name, pos, scale), move_direction(MOVE_DIRECTION::LEFT)
{
	speed = 10;
}

// ���� ������
Player::Player(const Player& origin) : GameObject(origin.name, origin.pos, origin.scale), move_direction(origin.move_direction)
{
	speed = origin.speed;
}

// �Ҹ���
Player::~Player()
{
}

// ���� �����ӿ� ������ �ʰ�, �̹� �����ӿ� ������ �� ȣ��Ǵ� �Լ�
void Player::OnKeyPressed(KEY_CODE key)
{
	switch (key)
	{
	case KEY_CODE::LEFT:
		move_direction = MOVE_DIRECTION::LEFT;
		break;
	case KEY_CODE::RIGHT:
		move_direction = MOVE_DIRECTION::RIGHT;
		break;
	default:
		assert(false);
		//throw GameException(L"�˸��� �̵�Ű�� �ƴմϴ�");
		//return;
	}

	Move();
}

// ���� �����ӿ��� Ű�� ���Ȱ�, �̹� �����ӿ��� ������ ��
void Player::OnKeyDown(KEY_CODE key)
{
	assert(key==KEY_CODE::LEFT || key==KEY_CODE::RIGHT);
	Move();
}

// �̵�
void Player::Move()
{
}