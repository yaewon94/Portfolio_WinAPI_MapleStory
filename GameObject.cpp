#include "PCH.h"
#include "GameObject.h"

#include "Engine.h"

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

// ������ (�� �����Ӹ��� ȣ��)
void GameObject::Render()
{
	HDC subDC = Engine::GetInstance().GetSubDC();
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
	HPEN prevPen = (HPEN)SelectObject(subDC, pen);
	Rectangle(subDC, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
	SelectObject(subDC, prevPen);
}