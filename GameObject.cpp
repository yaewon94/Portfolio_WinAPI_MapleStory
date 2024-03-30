#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "Component.h"

// ������
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale)
	: name(name), pos(pos), scale(scale)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin) : Entity(origin)//, GameObject(origin.name, origin.pos, origin.scale)
, name(origin.name), pos(origin.pos), scale(origin.scale)
{
	auto Capacity = origin.components.capacity();
	components.resize(Capacity);

	for (auto i=0; i<Capacity; ++i)
	{
		// [check] ���� Ÿ���� �˾Ƴ��� ��
		//this->components[i] = new T(origin.components[i]);
		this->components[i] = origin.components[i]->Clone();
	}
}

// �Ҹ���
GameObject::~GameObject()
{
	for (auto component : components)
	{
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void GameObject::Render()
{
	Engine::GetInstance().Render(*this);
}