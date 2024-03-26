#include "PCH.h"
#include "GameObject.h"

// ������
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale) 
	: Entity(name), pos(pos), scale(scale)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin) : Entity(origin.name), pos(origin.pos), scale(origin.scale)
{
}

// �Ҹ���
GameObject::~GameObject()
{
}
