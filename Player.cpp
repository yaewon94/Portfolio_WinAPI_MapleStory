#include "PCH.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Rigidbody.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : GameObject(name, pos, scale)
{
}

// ���� ������
Player::Player(const Player& origin) : GameObject(origin)
{
	*this = origin;
}

// �̵� ������
Player::Player(Player&& origin) noexcept : GameObject(std::move(origin))
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
	jumpPower = origin.jumpPower;
	return *this;
}

// �̵����� ������
Player& Player::operator=(Player&& origin) noexcept
{
	if (this != &origin)
	{
		speed = origin.speed;
		jumpPower = origin.jumpPower;
		origin.speed = 0;
		origin.jumpPower = 0;
	}
	return *this;
}

// �̹� �����ӿ� ó�� ������ �� ȣ��
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] Ű���� Ŀ���͸���¡ �� ���� �ڱⰡ ������ Ű����� �б���Ѿ� ��
	switch (key)
	{
	case KEY_CODE::LEFT:
		dir = Vec2::Left();
		Move();
		break;
	case KEY_CODE::RIGHT:
		dir = Vec2::Right();
		Move();
		break;
	case KEY_CODE::SHIFT:
		Jump();
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
	pos += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
}

// ����
void Player::Jump()
{
	static bool canJump = true;
	if (!canJump) return;
	canJump = false;

	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2::Up() * jumpPower);
}