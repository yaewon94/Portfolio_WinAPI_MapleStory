#include "PCH.h"
#include "GameObject.h"

// 생성자
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale) 
	: Entity(name), pos(pos), scale(scale)
{
}

// 복사 생성자
GameObject::GameObject(const GameObject& origin) : Entity(origin.name), pos(origin.pos), scale(origin.scale)
{
}

// 소멸자
GameObject::~GameObject()
{
}
