#include "PCH.h"
#include "AliveObject.h"

// ������
AliveObject::AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, pos, scale, layer), speed(speed), jumpPower(jumpPower)
{
}

// ���� ������
AliveObject::AliveObject(const AliveObject& origin) : GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
{
}

// �Ҹ���
AliveObject::~AliveObject()
{
}