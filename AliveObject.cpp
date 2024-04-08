#include "PCH.h"
#include "AliveObject.h"

// 생성자
AliveObject::AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, pos, scale, layer), speed(speed), jumpPower(jumpPower)
{
}

// 복사 생성자
AliveObject::AliveObject(const AliveObject& origin) : GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
{
}

// 소멸자
AliveObject::~AliveObject()
{
}