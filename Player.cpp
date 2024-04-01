#include "PCH.h"
#include "Player.h"
#include "GameObject.h"

// ������
Player::Player(GameObject& owner) : Component(owner)
{
}

// ���� ������
Player::Player(const Player& origin) : Component(origin)
{
	speed = origin.speed;
}

// �̵� ������
Player::Player(Player&& origin) noexcept : Component(std::move(origin))
{
	*this = std::move(origin);
}

// �Ҹ���
Player::~Player()
{
}

// ���� ������
Player& Player::operator=(const Player& origin)
{
	speed = origin.speed;
	return *this;
}

// �̵����� ������
Player& Player::operator=(Player&& origin) noexcept
{
	if (this != &origin)
	{
		speed = origin.speed;
		origin.speed = 0;
	}
	return *this;
}

// �̹� �����ӿ� ó�� ������ �� ȣ��
void Player::OnKeyPressed(KEY_CODE key)
{
	switch (key)
	{
	case KEY_CODE::LEFT:
		direction = MOVE_DIRECTION::LEFT;
		Move();
		break;
	case KEY_CODE::RIGHT:
		direction = MOVE_DIRECTION::RIGHT;
		Move();
		break;
	default:
		assert(false);
		//throw GameException(L"�˸��� �̵�Ű�� �ƴմϴ�");
		//return;
	}
}

// ���� �����ӿ��� ������, �̹� �����ӿ��� ������ �� ȣ��
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}

// �̵�
void Player::Move()
{
	Vec2 pos = GetOwner()->GetPos();
	pos.x += (int)direction * speed;
	GetOwner()->SetPos(Vec2(pos.x, pos.y));
}