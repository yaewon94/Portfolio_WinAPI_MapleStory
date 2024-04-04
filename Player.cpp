#include "PCH.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Rigidbody.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : GameObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
}

// ���� ������
Player::Player(const Player& origin) : GameObject(origin)
{
}

// �Ҹ���
Player::~Player()
{
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

// �浹 ����
void Player::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		GetComponent<Rigidbody>()->UseGravity(false);
		canJump = true;
	}
}

// �浹 ��
void Player::OnCollisionStay(GameObject& other)
{
	
}

// �浹 ����
void Player::OnCollisionExit(GameObject& other)
{
	GetComponent<Rigidbody>()->UseGravity(true);
	canJump = false;
}

// �̵�
void Player::Move()
{
	pos += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
}

// ����
void Player::Jump()
{
	if (!canJump) return;

	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2::Up() * jumpPower);
}