#include "PCH.h"
#include "Player.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 Scale) : GameObject(name, pos, scale)
{
}

// ���� ������
Player::Player(const Player& origin) : GameObject(origin.name, origin.pos, origin.scale)
{
}

// �Ҹ���
Player::~Player()
{
}