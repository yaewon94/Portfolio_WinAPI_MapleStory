#include "PCH.h"
#include "Player.h"

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 Scale) : GameObject(name, pos, scale)
{
}

// 복사 생성자
Player::Player(const Player& origin) : GameObject(origin.name, origin.pos, origin.scale)
{
}

// 소멸자
Player::~Player()
{
}