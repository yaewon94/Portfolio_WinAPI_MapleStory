#include "PCH.h"
#include "Player.h"

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 Scale) : GameObject(name, pos, scale), move_direction(MOVE_DIRECTION::LEFT)
{
	speed = 10;
}

// 복사 생성자
Player::Player(const Player& origin) : GameObject(origin.name, origin.pos, origin.scale), move_direction(origin.move_direction)
{
	speed = origin.speed;
}

// 소멸자
Player::~Player()
{
}

// 저번 프레임에 눌리지 않고, 이번 프레임에 눌렸을 때 호출되는 함수
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
		//throw GameException(L"알맞은 이동키가 아닙니다");
		//return;
	}

	Move();
}

// 저번 프레임에도 키가 눌렸고, 이번 프레임에도 눌렸을 때
void Player::OnKeyDown(KEY_CODE key)
{
	assert(key==KEY_CODE::LEFT || key==KEY_CODE::RIGHT);
	Move();
}

// 이동
void Player::Move()
{
}