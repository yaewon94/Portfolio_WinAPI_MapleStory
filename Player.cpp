#include "PCH.h"
#include "Player.h"
#include "Rigidbody.h"

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
}

// 복사 생성자
Player::Player(const Player& origin) : AliveObject(origin)
{
}

// 소멸자
Player::~Player()
{
}

// 이번 프레임에 처음 눌렸을 때 호출
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] 키세팅 커스터마이징 할 때는 자기가 셋팅한 키값대로 분기시켜야 함
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

// 저번 프레임에도 눌리고, 이번 프레임에도 눌렸을 때 호출
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}