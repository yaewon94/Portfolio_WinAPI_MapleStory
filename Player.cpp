#include "PCH.h"
#include "Player.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Rigidbody.h"

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : GameObject(name, pos, scale)
{
}

// 복사 생성자
Player::Player(const Player& origin) : GameObject(origin)
{
	*this = origin;
}

// 이동 생성자
Player::Player(Player&& origin) noexcept : GameObject(std::move(origin))
{
	*this = std::move(origin);
}

// 소멸자
Player::~Player()
{
}

// 대입 연산자
Player& Player::operator=(const Player& origin)
{
	speed = origin.speed;
	jumpPower = origin.jumpPower;
	return *this;
}

// 이동대입 연산자
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

// 이동
void Player::Move()
{
	pos += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
}

// 점프
void Player::Jump()
{
	static bool canJump = true;
	if (!canJump) return;
	canJump = false;

	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2::Up() * jumpPower);
}