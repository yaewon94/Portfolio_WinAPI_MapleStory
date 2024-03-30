#include "PCH.h"
#include "Player.h"
#include "GameObject.h"

// 생성자
Player::Player(GameObject* owner) : Component(owner)
{
}

// 복사 생성자
Player::Player(const Player& origin) : Component(origin)
{
	speed = origin.speed;
}

// 소멸자
Player::~Player()
{
}

// 이번 프레임에 처음 눌렸을 때 호출
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
		//throw GameException(L"알맞은 이동키가 아닙니다");
		//return;
	}
}

// 저번 프레임에도 눌리고, 이번 프레임에도 눌렸을 때 호출
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}

// 이동
void Player::Move()
{
	Vec2 pos = owner->GetPos();
	pos.x += (int)direction * speed;
	owner->SetPos(Vec2(pos.x, pos.y));
}